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
#ifdef USE_FBTHRIFT
#include <thrift/lib/cpp/protocol/TProtocol.h>
#else
#include <thrift/protocol/TProtocol.h>
#endif

#include <type_traits>
#include <utility>

namespace mox {
namespace details {
template <typename... Ts>
struct Ignore {};
}  // namespace details

template <class Obj, class = void>
struct is_thrift_object : std::false_type {};

template <class Obj>
struct is_thrift_object<
    Obj, typename std::conditional<false,
                                   details::Ignore<decltype(std::declval<Obj>().read(
                                       (::apache::thrift::protocol::TProtocol*)nullptr))>,
                                   void>::type> : std::true_type {};

template <class Obj>
inline constexpr bool is_thrift_object_v = is_thrift_object<Obj>::value;
}  // namespace mox
