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

#include "traits.h"

#include <catch2/catch_test_macros.hpp>

#include <type_traits>

#include "tutorial/protobuf/serialize/idl/types.pb.h"

TEST_CASE("test protobuf", "[traits]") {
  REQUIRE(mox::v1::is_protobuf_message<idl::pb::ClassType>::value);
  REQUIRE(mox::v2::is_protobuf_message<idl::pb::ClassType>::value);
  REQUIRE(mox::is_protobuf_message_v<idl::pb::ClassType>);
}
