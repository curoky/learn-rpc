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

#include "to_json.h"

#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

#include <condition_variable>
#include <initializer_list>
#include <string>
#include <type_traits>
#include <vector>

#include "library/serialization/fbthrift/idl/gen-cpp2/mock_types.h"

using json = nlohmann::json;

TEST_CASE("[fbthrift to json]") {
  idl::thrift::cpp2::StructType a;
  a.set_var_binary("13");
  REQUIRE(mox::is_thrift_object_v<idl::thrift::cpp2::StructType> == true);

  json a_json = a;
  REQUIRE(a_json.dump() != "");
  json pa_json = &a;
  REQUIRE(pa_json.dump() != "");
}
