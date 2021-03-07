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

use echo::{EchoSyncClient, Req, Rsp, TEchoSyncClient};
use thrift::{self, transport::TIoChannel};

fn main() {
    let mut channel = thrift::transport::TTcpChannel::new();
    channel.open("0.0.0.0:2300").unwrap();
    let (i_chan, o_chan) = channel.split().unwrap();

    let mut client = EchoSyncClient::new(
        thrift::protocol::TBinaryInputProtocol::new(
            thrift::transport::TFramedReadTransport::new(i_chan),
            false,
        ),
        thrift::protocol::TBinaryOutputProtocol::new(
            thrift::transport::TFramedWriteTransport::new(o_chan),
            true,
        ),
    );

    let rsp = client
        .echo(Req {
            message: Option::Some("hello world".to_string()),
        })
        .unwrap();

    println!("{:?}", rsp);
}
