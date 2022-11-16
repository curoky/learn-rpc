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

#include <catch2/catch_test_macros.hpp>

#include <string>

#include "flatbuffers/flatbuffers.h"
#include "tutorial/flatbuffers/serialize/idl/types_generated.h"

TEST_CASE("basic usage", "[flatbuffers][Serialize]") {
  flatbuffers::FlatBufferBuilder builder(1024);

  {
    auto str = builder.CreateString("123");
    auto ctb = idl::fbs::ClassTypeBuilder(builder);
    ctb.add_var_string(str);
    auto ct = ctb.Finish();
    builder.Finish(ct);
  }

  {
    const idl::fbs::ClassType* classType = idl::fbs::GetClassType(builder.GetBufferPointer());
    REQUIRE(classType->var_string()->string_view() == "123");
  }
}
