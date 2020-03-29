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
#include <stdint.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/protocol/TDebugProtocol.h>
#include <thrift/protocol/THeaderProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TTransport.h>

#include <memory>
#include <string>

namespace mox {
namespace detail {

template <typename ThriftStruct, typename Protocol>
std::string ThriftToString(const ThriftStruct& ts) {
  auto mbuffer = std::make_shared<apache::thrift::transport::TMemoryBuffer>();
  Protocol protocol(mbuffer);
  ts.write(&protocol);
  return mbuffer->getBufferAsString();  // NOLINT
}

template <typename ThriftStruct, typename Protocol>
ThriftStruct StringToThrift(const std::string& str) {
  using apache::thrift::transport::TMemoryBuffer;
  uint8_t* buf = reinterpret_cast<uint8_t*>(const_cast<char*>(str.data()));
  auto mbuffer =
      std::make_shared<TMemoryBuffer>(buf, str.size(), TMemoryBuffer::MemoryPolicy::OBSERVE);
  Protocol protocol(mbuffer);
  ThriftStruct result;
  result.read(&protocol);
  return result;
}
}  // namespace detail

template <typename ThriftStruct>
const auto ThriftToJson =
    detail::ThriftToString<ThriftStruct, apache::thrift::protocol::TJSONProtocol>;

template <typename ThriftStruct>
const auto ThriftToDebug =
    detail::ThriftToString<ThriftStruct, apache::thrift::protocol::TDebugProtocol>;

template <typename ThriftStruct>
const auto ThriftToBinary =
    detail::ThriftToString<ThriftStruct, apache::thrift::protocol::TBinaryProtocol>;

template <typename ThriftStruct>
const auto JsonToThrift =
    detail::StringToThrift<ThriftStruct, apache::thrift::protocol::TJSONProtocol>;

// template <typename ThriftStruct>
// const auto DebugToThrift = detail::StringToThrift<ThriftStruct,
// apache::thrift::protocol::TDebugProtocol>;

template <typename ThriftStruct>
const auto BinaryToThrift =
    detail::StringToThrift<ThriftStruct, apache::thrift::protocol::TBinaryProtocol>;

}  // namespace mox
