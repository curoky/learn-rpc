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

#include "serialize.h"

#include <catch2/catch_test_macros.hpp>

#include <string>

#include "tutorial/thrift/serialize/idl/gen-cpp/types_types.h"

TEST_CASE("json string", "[Serialize]") {
  // because of thrift's bug, skip this case;
  return;
  idl::thrift::StructType req;

  std::string serialize_data;

  SECTION("json protocol") {
    /*
    {
        "1":{"tf":0},
        "2":{"i8":0},
        "3":{"i16":0},
        "4":{"i32":0},
        "5":{"i64":0},
        "6":{"dbl":0},
        "7":{"str":""},
        "8":{"str":""},
        "9":{"str":""},
        "10":{"lst":["str",0]},
        "11":{"lst":["str",0]},
        "12":{"set":["str",0]},
        "13":{"map":["str","str",0,{}]},
        "14":{"i32":0},
        "15":{"set":["i32",0]},
        "16":{"rec":{}},"17":{"i32":0}
    }
    */
    serialize_data = mox::ThriftToJson<idl::thrift::StructType>(req);
    REQUIRE(req == mox::JsonToThrift<idl::thrift::StructType>(serialize_data));
  }

  SECTION("debug protocol") {
    /*
    StructType {
        01: var_bool (bool) = false,
        02: var_byte (byte) = 0x00,
        03: var_i16 (i16) = 0,
        04: var_i32 (i32) = 0,
        05: var_i64 (i64) = 0,
        06: var_double (double) = 0,
        07: var_string (string) = "",
        08: var_binary (string) = "",
        09: var_string_type (string) = "",
        10: var_string_list (list) = list<string>[0] {},
        11: var_binary_list (list) = list<string>[0] {},
        12: var_string_set (set) = set<string>[0] {},
        13: var_string_binary_map (map) = map<string,string>[0] {},
        14: var_enum (i32) = 0,
        15: var_enum_set (set) = set<i32>[0] {},
        16: var_union (struct) = UnionType {},
        17: var_required_i32 (i32) = 0,
    }
    */
    serialize_data = mox::ThriftToDebug<idl::thrift::StructType>(req);
    // debug protocol can't deserialize
  }

  SECTION("binary protocol") {
    serialize_data = mox::ThriftToBinary<idl::thrift::StructType>(req);
    REQUIRE(req == mox::BinaryToThrift<idl::thrift::StructType>(serialize_data));
  }
}
