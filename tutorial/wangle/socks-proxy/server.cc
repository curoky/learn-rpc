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
#include <gflags/gflags.h>
#include <openssl/ssl.h>
#include <stddef.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/Pipeline.h>

#include <memory>
#include <string>
#include <vector>

#include "ProxyFrontendPipelineFactory.h"

DEFINE_int32(port, 2323, "proxy server port");
DEFINE_int32(io, 1, "io thread num");

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  // folly::Init init(&argc, &argv);

  unsigned char key[100];
  std::string password = "123";
  EVP_BytesToKey(EVP_rc4(), EVP_md5(), NULL, (const unsigned char*)password.data(), password.size(),
                 1, key, NULL);

  wangle::ServerBootstrap<wangle::DefaultPipeline> server;
  server.childPipeline(std::make_shared<ProxyFrontendPipelineFactory>(
      std::string(reinterpret_cast<char*>(key), 16)));
  server.group(std::make_shared<folly::IOThreadPoolExecutor>(FLAGS_io));
  server.bind(FLAGS_port);
  server.waitForStop();
  return 0;
}
