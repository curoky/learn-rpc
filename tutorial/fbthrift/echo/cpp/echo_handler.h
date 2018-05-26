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
#include <memory>

#include "tutorial/fbthrift/echo/idl/gen-cpp2/Echo.h"

class EchoHandler : public echo::cpp2::EchoSvIf {
 public:
  void echo(echo::cpp2::Rsp& rsp, std::unique_ptr<echo::cpp2::Req> req) override {
    rsp.set_message(req->get_message());
    LOG(INFO) << "[echo]: counter->" << echo_counter++;
  }

 private:
  std::atomic<int> echo_counter{0};
  std::atomic<int> oneway_echo_counter{0};
};
