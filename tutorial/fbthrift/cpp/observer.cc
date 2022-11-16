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

#include <catch2/catch_test_macros.hpp>
#include <folly/SocketAddress.h>
#include <folly/io/async/AsyncSocket.h>
#include <folly/io/async/EventBase.h>
#include <folly/io/async/Request.h>
#include <glog/logging.h>
#include <thrift/lib/cpp/concurrency/ThreadManager.h>
#include <thrift/lib/cpp/protocol/TProtocolTypes.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>
#include <thrift/lib/cpp2/server/BaseThriftServer.h>
#include <thrift/lib/cpp2/server/ThriftServer.h>

#include <atomic>
#include <chrono>
#include <memory>
#include <ostream>
#include <thread>
#include <utility>

#include "tutorial/fbthrift/echo/cpp/echo_handler.h"
#include "tutorial/fbthrift/echo/idl/gen-cpp2/Echo.h"

std::unique_ptr<apache::thrift::ThriftServer> create_echo_server(int port) {
  auto handler = std::make_shared<EchoHandler>();
  auto proc_factory =
      std::make_shared<apache::thrift::ThriftServerAsyncProcessorFactory<EchoHandler>>(handler);
  auto server = std::make_unique<apache::thrift::ThriftServer>();
  server->setPort(port);
  server->setProcessorFactory(proc_factory);
  return server;
}

class EchoTmObserver : public apache::thrift::concurrency::ThreadManager::Observer {
  using RunStats = apache::thrift::concurrency::ThreadManager::RunStats;

 public:
  void preRun(folly::RequestContext*) override {
    //
    LOG(INFO) << "[preRun]" << pre_count_++;
  }
  void postRun(folly::RequestContext*, const RunStats&) override {
    //
    LOG(INFO) << "[postRun]" << post_count_++;
  }

 public:
  std::atomic<int> pre_count_{0};
  std::atomic<int> post_count_{0};
};

TEST_CASE("basic usage", "[Observer]") {
  std::atomic_bool exited{false};
  // create server
  std::unique_ptr<apache::thrift::ThriftServer> server = create_echo_server(2333);
  auto observer = std::make_shared<EchoTmObserver>();

  // Setup observer for all tmgr
  apache::thrift::concurrency::ThreadManager::setGlobalObserver(observer);
  // Setup observer for special server
  // Note: when use PriorityThreadManager(by default), addTaskObserver is not impl,
  // because PriorityThreadManager hold a list of ThreadManager.
  // auto tm = std::dynamic_pointer_cast<apache::thrift::concurrency::ThreadManager>(
  //     server->getThreadManager());
  // auto tm = server->getThreadManager_deprecated();
  // REQUIRE(tm != nullptr);
  // tm->addTaskObserver(observer);

  std::thread th([&server, &exited]() {
    server->serve();
    exited.store(true);
  });
  std::this_thread::sleep_for(std::chrono::seconds(4));

  // create client
  folly::EventBase evb;
  folly::AsyncSocket::UniquePtr sock(
      new folly::AsyncSocket(&evb, folly::SocketAddress("0.0.0.0", 2333)));
  auto chan = apache::thrift::HeaderClientChannel::newChannel(
      std::move(sock), apache::thrift::HeaderClientChannel::Options().setProtocolId(
                           apache::thrift::protocol::T_BINARY_PROTOCOL));
  auto client = std::make_unique<echo::cpp2::EchoAsyncClient>(std::move(chan));

  echo::cpp2::Req req;
  echo::cpp2::Rsp rsp;

  REQUIRE(observer->pre_count_.load() == 3);
  REQUIRE(observer->post_count_.load() == 3);
  client->sync_echo(rsp, req);
  REQUIRE(observer->pre_count_.load() == 4);
  REQUIRE(observer->post_count_.load() == 4);

  server->stop();
  while (exited.load() == false) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  server.reset();
  th.join();
}
