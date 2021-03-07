/*
 * Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
 *
 * This file is part of learn-rpc.
 * See https://github.com/curoky/learn-rpc for further info.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

use echo::{EchoSyncHandler, EchoSyncProcessor, Req, Rsp};
use thrift;

struct EchoServer {}

impl EchoSyncHandler for EchoServer {
    fn handle_echo(&self, req: Req) -> thrift::Result<Rsp> {
        println!("handling echo: {:?}", req);
        Ok(Rsp {
            message: req.message,
        })
    }
}

fn main() {
    let mut server = thrift::server::TServer::new(
        thrift::transport::TFramedReadTransportFactory::new(),
        thrift::protocol::TBinaryInputProtocolFactory::new(),
        thrift::transport::TFramedWriteTransportFactory::new(),
        thrift::protocol::TBinaryOutputProtocolFactory::new(),
        EchoSyncProcessor::new(EchoServer {}),
        10,
    );
    server.listen("0.0.0.0:2300").unwrap();
}
