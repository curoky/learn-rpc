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
// #include <folly/io/async/AsyncSocket.h>  // for AsyncSocket, AsyncSocket::UniquePtr
// #include <folly/io/async/EventBase.h>    // for EventBase
// #include <folly/io/async/Request.h>      // for RequestContext
#include <glog/logging.h>
// #include <thrift/lib/cpp/concurrency/ThreadManager.h>  // for ThreadManager,
// ThreadManager::Observer, ThreadManager::RunStats #include
// <thrift/lib/cpp/protocol/TProtocolTypes.h>     // for T_BINARY_PROTOCOL #include
// <thrift/lib/cpp2/async/HeaderClientChannel.h>  // for HeaderClientChannel #include
// <thrift/lib/cpp2/server/BaseThriftServer.h>    // for ThriftServerAsyncProcessorFactory
#include <thrift/lib/cpp2/server/ThriftServer.h>

// #include "echo_service_handler.h"                                  // for EchoHandler
#include "tutorial/fbthrift/echo/idl/gen-cpp2/Echo.h"

DEFINE_int32(port, 9999, "server port");

int main(int argc, char *argv[]) {
  folly::init(&argc, &argv);
  FLAGS_logtostderr = true;
  FLAGS_colorlogtostderr = true;

  auto handler = std::make_shared<EchoHandler>();
  auto proc_factory =
      std::make_shared<apache::thrift::ThriftServerAsyncProcessorFactory<EchoHandler>>(handler);
  auto server = std::make_unique<apache::thrift::ThriftServer>();
  server->setPort(FLAGS_port);
  server->setProcessorFactory(proc_factory);

  server->serve();

  // folly::Baton<> exited;
  // std::thread th([&server, &exited]() {
  //   exited.post();
  // });
  // th.join();
  return 0;
}
