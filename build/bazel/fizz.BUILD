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

load("@rules_cc//cc:defs.bzl", "cc_library")
load("@com_github_curoky_learn_rpc//:build/bazel/copts.bzl", "DEFAULT_CPP_COPTS")

cc_library(
    name = "fizz",
    srcs = glob(
        ["fizz/**/*.cpp"],
        exclude = [
            "fizz/**/test/**/*.cpp",
            "fizz/experimental/crypto/**",
            "fizz/tool/**",
            "fizz/**/javacrypto/**/*.cpp",
        ],
    ),
    hdrs = glob(["fizz/**/*.h"]),
    copts = DEFAULT_CPP_COPTS,
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        "@com_github_curoky_learn_rpc//source/folly",
        "@com_github_facebook_zstd//:zstd",
        "@com_github_google_brotli//:brotlidec",
        "@com_github_google_brotli//:brotlienc",
        "@com_github_jedisct1_libsodium//:libsodium",
    ],
)
