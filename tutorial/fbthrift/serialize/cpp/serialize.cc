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

#include <catch2/catch.hpp>
#include <folly/File.h>
#include <folly/ScopeGuard.h>

#include <utility>

#include "library/serialization/fbthrift/idl/gen-cpp2/mock_types.h"

TEST_CASE("zero copy", "[Serialize]") {
  {
    idl::thrift::cpp2::StructType req;
    req.set_var_string("hhh");

    auto file = folly::File::temporary();
    SCOPE_EXIT { file.close(); };
  }
}
