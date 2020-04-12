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
#include <nlohmann/json.hpp>
#include <thrift/lib/cpp2/protocol/DebugProtocol.h>
#include <thrift/lib/cpp2/protocol/Serializer.h>

#include <iostream>
#include <string>
#include <utility>

#define USE_FBTHRIFT
#include "library/serialization/thrift/traits.h"

namespace nlohmann {
template <typename BasicJsonType, typename T,
          std::enable_if_t<mox::is_thrift_object<T>::value, int> = 0>
void from_json_base(const BasicJsonType& j, T& b) {
  apache::thrift::JSONSerializer::deserialize(j.dumps(), b);
}

template <typename BasicJsonType, typename T,
          std::enable_if_t<mox::is_thrift_object<T>::value, int> = 0>
void to_json(BasicJsonType& j, const T& b) {
  j = BasicJsonType::parse(apache::thrift::SimpleJSONSerializer::serialize<std::string>(b));
}

template <typename BasicJsonType, typename T,
          std::enable_if_t<mox::is_thrift_object<T>::value, int> = 0>
void to_json(BasicJsonType& j, const T* b) {
  j = BasicJsonType::parse(apache::thrift::SimpleJSONSerializer::serialize<std::string>(*b));
}
}  // namespace nlohmann
