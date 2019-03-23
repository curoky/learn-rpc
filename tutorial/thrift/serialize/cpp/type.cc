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
#include <stdint.h>

#include <map>
#include <set>
#include <string>
#include <typeinfo>
#include <vector>

#include "gen-cpp/mock_constants.h"  // for g_mock_constants, mockConstants
#include "gen-cpp/mock_types.h"      // for MockRequest, EnumType::type, EnumType

#define REQUIRE_TYPE(var, type) REQUIRE(typeid(var) == typeid(type));

TEST_CASE("basic type", "[Type]") {
  idl::thrift::StructType req;
  REQUIRE_TYPE(req.var_bool, bool);
  REQUIRE_TYPE(req.var_byte, int8_t);
  REQUIRE_TYPE(req.var_i16, int16_t);
  REQUIRE_TYPE(req.var_i32, int32_t);
  REQUIRE_TYPE(req.var_i64, int64_t);
  REQUIRE_TYPE(req.var_double, double);

  REQUIRE_TYPE(req.var_string, std::string);
  REQUIRE_TYPE(req.var_binary, std::string);
}

TEST_CASE("container type", "[Type]") {
  idl::thrift::StructType req;
  REQUIRE_TYPE(req.var_string_list, std::vector<std::string>);
  REQUIRE_TYPE(req.var_binary_list, std::vector<std::string>);

  REQUIRE_TYPE(req.var_string_set, std::set<std::string>);

  using StringMap = std::map<std::string, std::string>;
  REQUIRE_TYPE(req.var_string_binary_map, StringMap);
}

TEST_CASE("enum type", "[Type]") {
  idl::thrift::StructType req;
  REQUIRE_TYPE(req.var_enum, idl::thrift::EnumType::type);
  REQUIRE_TYPE(req.var_enum_set, std::set<idl::thrift::EnumType::type>);
}

TEST_CASE("constant type", "[Type]") {
  idl::thrift::StructType req;
  REQUIRE_TYPE(idl::thrift::g_types_constants.GLOBAL_CONST_VAR_STRING, std::string);
  REQUIRE(idl::thrift::g_types_constants.GLOBAL_CONST_VAR_STRING == "123");
}
