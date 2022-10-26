# Copyright (c) 2018-2022 curoky(cccuroky@gmail.com).
#
# This file is part of learn-rpc.
# See https://github.com/curoky/learn-rpc for further info.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load("//:build/bazel/copts.bzl", "TEST_CPP_COPTS", "TEST_LINKOPTS")
load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "echo_handler",
    testonly = False,
    srcs = [
        "echo_handler.h",
    ] + ["//tutorial/fbthrift/echo/idl:echo_fbthrift"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "//source/fbthrift",
    ],
)

cc_binary(
    name = "client",
    testonly = False,
    srcs = [
        "client.cc",
    ] + ["//tutorial/fbthrift/echo/idl:echo_fbthrift"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "//source/fbthrift",
    ],
)

cc_binary(
    name = "server",
    testonly = False,
    srcs = [
        "server.cc",
        "echo_handler.h",
    ] + ["//tutorial/fbthrift/echo/idl:echo_fbthrift"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "//source/fbthrift",
    ],
)

cc_binary(
    name = "co_client",
    testonly = False,
    srcs = [
        "co_client.cc",
    ] + ["//tutorial/fbthrift/echo/idl:echo_fbthrift"],
    copts = TEST_CPP_COPTS,
    linkopts = TEST_LINKOPTS,
    deps = [
        "//source/fbthrift",
        "//source/folly",
    ],
)
