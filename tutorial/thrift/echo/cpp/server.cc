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

#include <spdlog/spdlog.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>

#include <string>

#include "tutorial/thrift/echo/idl/gen-cpp/Echo.h"
#include "tutorial/thrift/echo/idl/gen-cpp/echo_types.h"

class EchoHandler : public echo::EchoIf {
 public:
  ~EchoHandler() override = default;
  void echo(echo::Rsp& rsp, const echo::Req& req) override {
    rsp.message = req.message;
    spdlog::info("EchoHandler::recv: {}", req.message);
  }
};

int main(int argc, char* argv[]) {
  auto iterface = std::make_shared<EchoHandler>();
  auto processor = std::make_shared<echo::EchoProcessor>(iterface);

  auto socket = std::make_shared<apache::thrift::transport::TServerSocket>(9090);
  auto transport_factory = std::make_shared<apache::thrift::transport::TFramedTransportFactory>();
  auto protocol_factory = std::make_shared<apache::thrift::protocol::TBinaryProtocolFactory>();

  apache::thrift::server::TSimpleServer server(processor, socket, transport_factory,
                                               protocol_factory);
  server.serve();
  return 0;
}
