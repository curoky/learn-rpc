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

import logging
import time

from thrift.protocol.TBinaryProtocol import (TBinaryProtocol,
                                             TBinaryProtocolFactory)
# from thrift.protocol.THeaderProtocol import THeaderProtocol, THeaderProtocolFactory
from thrift.transport import TSocket
# from thrift.protocol.TSimpleJSONProtocol import TSimpleJSONProtocol, TSimpleJSONProtocolFactory
from thrift.transport.TTransport import (TFramedTransport,
                                         TFramedTransportFactory,
                                         TMemoryBuffer)


class SimpleClient:

    def __init__(
            self,
            client_type,
            host='0.0.0.0',
            port='8080',
            transport_factory=TFramedTransportFactory(),
            serialize_factory=TBinaryProtocolFactory(),
    ):
        self.logger = logging.getLogger(__class__.__name__)
        self.socket = TSocket.TSocket(host=host, port=port)
        self.transport = transport_factory.getTransport(self.socket)
        self.protocol = serialize_factory.getProtocol(self.transport)
        self.client = client_type(self.protocol)

    def __getattr__(self, method):

        def call(*args, **kwargs):
            st = time.time_ns()
            self.logger.info(f'Call[{method}]: start')
            try:
                self.transport.open()
                func = getattr(self.client, method)
                rsp = func(*args, **kwargs)
                self.logger.info(f'Call[{method}]: success! ({(time.time_ns()-st)/1000}ms)')
                return rsp
            except Exception as e:
                self.logger.error(f'Call[{method}]: error! {e}')
                raise
            finally:
                self.transport.close()

        return call
