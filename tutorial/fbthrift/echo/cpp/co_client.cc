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

#include <folly/SocketAddress.h>
#include <folly/init/Init.h>
#include <folly/io/async/AsyncSocket.h>
#include <glog/logging.h>
#include <thrift/lib/cpp/protocol/TProtocolTypes.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>

#include <iostream>

#include "tutorial/fbthrift/echo/idl/gen-cpp2/Echo.h"

DEFINE_int32(port, 9999, "server port");

int main(int argc, char *argv[]) {
  // std::cout << __cpp_coroutines << ": "<< __cpp_impl_coroutine<< std::endl;

  // folly::init(&argc, &argv);
  // FLAGS_logtostderr = true;
  // FLAGS_colorlogtostderr = true;

  // folly::EventBase evb;
  // auto sock = folly::AsyncSocket::newSocket(&evb, folly::SocketAddress("0.0.0.0", FLAGS_port));
  // auto chan = apache::thrift::HeaderClientChannel::newChannel(std::move(sock));
  // chan->setProtocolId(apache::thrift::protocol::T_BINARY_PROTOCOL);
  // auto client = std::make_unique<idl::thrift::cpp2::EchoAsyncClient>(std::move(chan));

  // ::idl::thrift::cpp2::StructType req;
  // ::idl::thrift::cpp2::MockResponse rsp;
  // LOG(INFO) << "send echo";
  // // client->co_echo(rsp, req);
  // folly::coro::Task<::idl::thrift::cpp2::MockResponse> rsp = client->co_echo(req);
  // // rsp.assign();
  // // client->sync_echo(rsp, req);
  // LOG(INFO) << "recv echo";
}
