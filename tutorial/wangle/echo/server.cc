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

#include <folly/executors/IOThreadPoolExecutor.h>
#include <folly/init/Init.h>
#include <folly/io/async/AsyncServerSocket.h>
#include <folly/portability/GFlags.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

DEFINE_uint32(port, 8888, "server listen port");

typedef wangle::Pipeline<folly::IOBufQueue&, std::string> EchoPipeline;

// the main logic of our echo server; receives a string and writes it straight
// back
class EchoHandler : public wangle::HandlerAdapter<std::string> {
 public:
  void read(Context* ctx, std::string msg) override {
    LOG(INFO) << "handling " << msg;

    write(ctx, msg + "\r\n");
  }
};

// where we define the chain of handlers for each messeage received
class EchoPipelineFactory : public wangle::PipelineFactory<EchoPipeline> {
 public:
  EchoPipeline::Ptr newPipeline(std::shared_ptr<folly::AsyncTransport> sock) override {
    auto pipeline = EchoPipeline::create();
    pipeline->addBack(wangle::AsyncSocketHandler(sock));
    pipeline->addBack(wangle::LineBasedFrameDecoder(8192));
    pipeline->addBack(wangle::StringCodec());
    pipeline->addBack(EchoHandler());
    pipeline->finalize();
    return pipeline;
  }
};

class TcpServer : public wangle::ServerBootstrap<EchoPipeline> {};

int main(int argc, char** argv) {
  folly::init(&argc, &argv);

  folly::SocketAddress addr("0.0.0.0", FLAGS_port);

  TcpServer server;
  server.childPipeline(std::make_shared<EchoPipelineFactory>());
  server.bind(addr);
  server.waitForStop();
  return 0;
}
