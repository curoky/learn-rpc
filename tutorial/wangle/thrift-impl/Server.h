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
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <thrift/lib/cpp/TProcessor.h>
#include <thrift/lib/cpp/protocol/TBinaryProtocol.h>
#include <thrift/lib/cpp/transport/TBufferTransports.h>
#include <thrift/lib/cpp/transport/TTransport.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/channel/EventBaseHandler.h>
#include <wangle/codec/LengthFieldBasedFrameDecoder.h>
#include <wangle/codec/LengthFieldPrepender.h>
#include <wangle/service/ExecutorFilter.h>
#include <wangle/service/ServerDispatcher.h>
#include <wangle/service/Service.h>

#include <memory>
#include <utility>

namespace mox {
typedef wangle::Pipeline<folly::IOBufQueue&, std::unique_ptr<folly::IOBuf>> ThriftPipeline;

class ThriftHandler : public wangle::HandlerAdapter<std::unique_ptr<folly::IOBuf>> {
 public:
  explicit ThriftHandler(std::shared_ptr<apache::thrift::TProcessor> processor)
      : processor_(processor) {}

  std::unique_ptr<folly::IOBuf> process(std::unique_ptr<folly::IOBuf> unframed) {
    // Note: unframed from IOBufQueue->split(), may be chained.
    unframed->coalesce();
    CHECK(unframed->isChained() == false);

    static apache::thrift::protocol::TBinaryProtocolFactory inProtoFac, outProtoFac;

    auto inProto =
        inProtoFac.getProtocol(std::make_shared<apache::thrift::transport::TMemoryBuffer>(
            unframed->writableData(), unframed->length()));
    auto outBuf =
        std::make_shared<apache::thrift::transport::TMemoryBuffer>(static_cast<uint32_t>(1024));
    auto outProto = outProtoFac.getProtocol(outBuf);

    // spdlog::info("recv: {}", unframed->to<std::string>());
    processor_->process(inProto, outProto, nullptr);
    return outBuf->cloneBufferAsIOBuf();
  }

  void read(Context* ctx, std::unique_ptr<folly::IOBuf> unframed) override {
    write(ctx, process(std::move(unframed)));
  }

 private:
  std::shared_ptr<apache::thrift::TProcessor> processor_;
};

class ThriftService : public wangle::Service<std::unique_ptr<folly::IOBuf>> {
 public:
  explicit ThriftService(std::shared_ptr<apache::thrift::TProcessor> processor) {
    handler_ = std::make_unique<ThriftHandler>(processor);
  }

  folly::Future<std::unique_ptr<folly::IOBuf>> operator()(
      std::unique_ptr<folly::IOBuf> unframed) override {
    return folly::makeFuture(handler_->process(std::move(unframed)));
  }

 private:
  std::unique_ptr<ThriftHandler> handler_;
};

class ThriftPipelineFactory : public wangle::PipelineFactory<ThriftPipeline> {
 public:
  explicit ThriftPipelineFactory(std::shared_ptr<apache::thrift::TProcessor> processor)
      : processor_(processor) {
    service_ = std::make_unique<wangle::ExecutorFilter<std::unique_ptr<folly::IOBuf>>>(
        std::make_shared<folly::CPUThreadPoolExecutor>(30),
        std::make_shared<ThriftService>(processor));
  }

  ThriftPipeline::Ptr newPipeline(std::shared_ptr<folly::AsyncTransport> sock) {
    auto pipeline = ThriftPipeline::create();
    pipeline->addBack(wangle::AsyncSocketHandler(sock));
    pipeline->addBack(wangle::EventBaseHandler());
    pipeline->addBack(wangle::LengthFieldBasedFrameDecoder());
    pipeline->addBack(wangle::LengthFieldPrepender());

    // pipeline->addBack(ThriftHandler(processor_));
    pipeline->addBack(
        wangle::MultiplexServerDispatcher<std::unique_ptr<folly::IOBuf>>(service_.get()));

    pipeline->finalize();
    return pipeline;
  }

 private:
  std::shared_ptr<apache::thrift::TProcessor> processor_;
  std::unique_ptr<wangle::ExecutorFilter<std::unique_ptr<folly::IOBuf>>> service_;
};
}  // namespace mox
