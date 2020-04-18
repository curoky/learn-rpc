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

#pragma once
#include <folly/SocketAddress.h>
#include <thrift/lib/cpp/TProcessor.h>
#include <wangle/acceptor/ServerSocketConfig.h>

#include <memory>
#include <vector>

namespace folly {
class EventBase;
class IOThreadPoolExecutor;
class AsyncServerSocket;
}  // namespace folly

namespace wangle {
class ServerSocketFactory;
class AsyncServerSocketFactory;
}  // namespace wangle
namespace mox {

class Acceptor;
class Server {
 public:
  explicit Server(std::shared_ptr<apache::thrift::TProcessor> processor);

  void serve();
  void stop();

  void join();

  void bind(folly::SocketAddress& address);

  void setNumIOWorkerThreads(int size) {}

 private:
  wangle::ServerSocketConfig accConfig_;

  folly::EventBase* serveEventBase_{nullptr};

  std::shared_ptr<folly::IOThreadPoolExecutor> acceptorGroup_;
  std::shared_ptr<folly::IOThreadPoolExecutor> ioGroup_;
  std::shared_ptr<std::vector<std::shared_ptr<folly::AsyncServerSocket>>> sockets_{
      std::make_shared<std::vector<std::shared_ptr<folly::AsyncServerSocket>>>()};
  std::vector<std::shared_ptr<Acceptor>> acceptors_;

  std::shared_ptr<wangle::AsyncServerSocketFactory> socketFactory_;

  std::shared_ptr<apache::thrift::TProcessor> processor_;
};

}  // namespace mox
