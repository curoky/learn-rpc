#!/usr/bin/env python3
# Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
#
# This file is part of learn-rpc.
# See https://github.com/curoky/learn-rpc for further info.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
'''
Proxy Buffered to Framed
-----------------------

Start a server(on port A), receive thrift buffered message, transform to framed
and forward to another server(on port B).
'''

import io
import logging
from typing import Union

import typer
from thrift.protocol import TBinaryProtocol, TCompactProtocol, TJSONProtocol
from thrift.server import TServer
from thrift.transport import TSocket, TTransport
from thrift_tools.thrift_message import ThriftMessage
from thrift_tools.thrift_struct import ThriftStruct

logger = logging.getLogger(__name__)


class TBufferedMemoryTransport(TTransport.TBufferedTransport):
    '''
    Like TBufferedTransport, but save all read data in memory buffer.
    '''

    def __init__(self, trans):
        super().__init__(trans)
        self._buffer = io.BytesIO(b'')

        # Note: read first 4 byte for detect protocol.
        self.__already_read_first_byte = False
        self._buffer.write(super().read(4))

    def read(self, sz):
        if not self.__already_read_first_byte:
            self.__already_read_first_byte = True
            return self._buffer.getvalue()
        buf = super().read(sz)
        self._buffer.write(buf)
        return buf


def ReadThriftMessage(proto: Union[TBinaryProtocol.TBinaryProtocol,
                                   TCompactProtocol.TCompactProtocol, TJSONProtocol.TJSONProtocol]):
    '''Deserialize a message from proto to ThriftMessage.
    '''

    # unpack the message
    method, mtype, seqid = proto.readMessageBegin()

    if len(method) == 0 or method.isspace() or method.startswith(' '):
        raise ValueError('no method name')

    if len(method) > ThriftMessage.MAX_METHOD_LENGTH:
        raise ValueError('method name too long')

    # we might have made it until this point by mere chance, so filter out
    # suspicious method names
    valid = range(33, 127)
    if any(ord(char) not in valid for char in method):
        raise ValueError('invalid method name' % method)

    args = ThriftStruct.read(proto,
                             max_fields=ThriftMessage.MAX_FIELDS,
                             max_list_size=ThriftMessage.MAX_LIST_SIZE,
                             max_map_size=ThriftMessage.MAX_MAP_SIZE,
                             max_set_size=ThriftMessage.MAX_SET_SIZE,
                             read_values=False)

    proto.readMessageEnd()

    return ThriftMessage(method, mtype, seqid, args, None, 0)


class ProxyServer(TServer.TThreadPoolServer):
    ''' Base on TThreadPoolServer, rewrite serveClient method.
    '''

    def __init__(self, listen_ip: str, listen_port: int, to_ip: str, to_port: int):
        transport = TSocket.TServerSocket(host=listen_ip, port=listen_port)
        super().__init__(None, transport)
        self.to_ip = to_ip
        self.to_port = to_port

    def serveClient(self, client: TSocket.TSocket):
        logger.info(f'recv client {client._address}')
        _, raw_message = self.recvMessage(client)
        logger.info(f'recv message, len: {len(raw_message)}')
        self.sendMessage(message=raw_message)

    def recvMessage(self, socket: TSocket.TSocket):
        itrans = TBufferedMemoryTransport(socket)
        iprot = ThriftMessage.detect_protocol(itrans._buffer.getbuffer(),
                                              default=TBinaryProtocol.TBinaryProtocol)(itrans)

        thrift_message = ReadThriftMessage(iprot)
        raw_message = itrans._buffer.getvalue()
        return thrift_message, raw_message

    def sendMessage(self, message: bytes):
        otrans = TTransport.TFramedTransport(
            trans=TSocket.TSocket(host=self.to_ip, port=self.to_port))
        try:
            otrans.open()
            otrans.write(message)
            otrans.flush()
            otrans.readFrame()
            logger.info(f'send message: recv len: {len(otrans.cstringio_buf.getvalue())}')
        except Exception as e:
            logger.error(f'write to target port {self.to_port} failed: {e}')
        finally:
            otrans.close()


app = typer.Typer()


@app.command()
def main(listen_ip: str = '0.0.0.0',
         listen_port: int = 8991,
         proxy_to_ip: str = '0.0.0.0',
         proxy_to_port: int = 8990):
    logger.info(f'start: {listen_ip}:{listen_port} -> {proxy_to_ip}:{proxy_to_port}')

    server = ProxyServer(listen_ip, listen_port, proxy_to_ip, proxy_to_port)

    logger.info('Starting the server...')
    server.serve()
    logger.info('done.')


if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    app()
