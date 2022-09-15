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
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def pkg_rules_dependencies():
    http_archive(
        name = "com_github_abseil_abseil_cpp",
        urls = [
            "https://github.com/abseil/abseil-cpp/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "abseil-cpp-master",
    )

    http_archive(
        name = "hedron_compile_commands",
        urls = [
            "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "bazel-compile-commands-extractor-main",
    )

    http_archive(
        name = "com_github_google_benchmark",
        urls = [
            "https://github.com/google/benchmark/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "benchmark-main",
    )

    http_archive(
        name = "com_github_google_boringssl",
        urls = [
            "https://github.com/google/boringssl/archive/refs/heads/master-with-bazel.tar.gz",
        ],
        strip_prefix = "boringssl-master-with-bazel",
    )

    http_archive(
        name = "com_github_google_brotli",
        urls = [
            "https://github.com/google/brotli/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "brotli-master",
    )

    http_archive(
        name = "com_github_catchorg_catch2",
        urls = [
            "https://github.com/catchorg/Catch2/archive/refs/heads/devel.tar.gz",
        ],
        strip_prefix = "Catch2-devel",
        build_file = "@com_curoky_tame//:recipes/c/catch2/v3/BUILD",
        patch_cmds = ["mv src/catch2/catch_all.hpp src/catch2/catch.hpp"],
    )

    http_archive(
        name = "com_github_facebook_fatal",
        urls = [
            "https://github.com/facebook/fatal/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "fatal-main",
        build_file = "@com_curoky_tame//:recipes/f/fatal/default/BUILD",
    )

    http_archive(
        name = "com_github_facebook_fbthrift",
        urls = [
            "https://github.com/facebook/fbthrift/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "fbthrift-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/f/fbthrift/default/BUILD",
        patch_cmds = [
            "sed -i -e 's/folly::badge<ThriftServer>{},//g' thrift/lib/cpp2/server/ThriftServer.cpp",
            "sed -i -e 's/folly::badge<ThriftServer>,//g' thrift/lib/cpp2/server/ThriftServer.h",
        ],
    )

    http_archive(
        name = "com_github_facebookincubator_fizz",
        urls = [
            "https://github.com/facebookincubator/fizz/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "fizz-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/f/fizz/default/BUILD",
    )

    http_archive(
        name = "com_github_facebook_folly",
        urls = [
            "https://github.com/facebook/folly/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "folly-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/f/folly/default/BUILD",
        patch_cmds = [
            "sed -i -e 's/constexpr ::folly::detail::safe_assert_terminate_w/::folly::detail::safe_assert_terminate_w/g' folly/lang/SafeAssert.h",
        ],
    )

    http_archive(
        name = "com_github_gflags_gflags",
        urls = [
            "https://github.com/gflags/gflags/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "gflags-master",
    )

    http_archive(
        name = "com_github_google_glog",
        urls = ["https://github.com/google/glog/archive/refs/tags/v0.5.0.tar.gz"],
        strip_prefix = "glog-0.5.0",
    )

    http_archive(
        name = "com_google_googleapis",
        urls = [
            "https://github.com/googleapis/googleapis/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "googleapis-master",
    )

    http_archive(
        name="com_github_google_googletest",
        urls=[
            "https://github.com/google/googletest/archive/refs/heads/main.tar.gz"
        ],
        strip_prefix="googletest-main",
    )

    http_archive(
        name = "com_github_grpc_grpc",
        urls = ["https://github.com/grpc/grpc/archive/refs/heads/master.tar.gz"],
        strip_prefix = "grpc-master",
    )

    http_archive(
        name = "com_pagure_libaio",
        urls = [
            "https://pagure.io/libaio/archive/libaio-0.3.113/libaio-libaio-0.3.113.tar.gz",
        ],
        strip_prefix = "libaio-libaio-0.3.113",
        build_file = "@com_curoky_tame//:recipes/l/libaio/default/BUILD",
    )

    http_archive(
        name = "com_google_protobuf",
        urls = [
            "https://github.com/protocolbuffers/protobuf/archive/refs/tags/v3.19.4.tar.gz",
        ],
        strip_prefix = "protobuf-3.19.4",
        patch_cmds = ["sed -i -e 's/@zlib/@net_zlib_zlib/g' BUILD"],
    )

    http_archive(
        name = "com_github_facebook_proxygen",
        urls = [
            "https://github.com/facebook/proxygen/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "proxygen-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/p/proxygen/default/BUILD",
    )

    http_archive(
        name = "rules_bison",
        urls = [
            "https://github.com/jmillikin/rules_bison/archive/refs/tags/v0.2.tar.gz",
        ],
        strip_prefix = "rules_bison-0.2",
        patch_cmds = ["sed -i '83d' bison/bison.bzl"],
    )

    http_archive(
        name = "com_github_nelhage_rules_boost",
        urls = [
            "https://github.com/nelhage/rules_boost/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "rules_boost-master",
        patch_cmds = [
            # "sed -i -e 's/openssl/org_openssl/g' boost/boost.bzl",
            # "sed -i -e 's/org_lzma_lzma/org_xz_xz/g' boost/boost.bzl",
            # "sed -i -e 's?org_lzma_lzma//:lzma?org_xz_xz//:xz?g' BUILD.boost",
            # "sed -i -e 's/org_lzma_lzma/org_xz_xz/g' BUILD.lzma"
        ],
    )

    http_archive(
        name = "rules_flex",
        urls = [
            "https://github.com/jmillikin/rules_flex/archive/refs/tags/v0.2.tar.gz",
        ],
        strip_prefix = "rules_flex-0.2",
        patch_cmds = ["sed -i '76d' flex/flex.bzl"],
    )

    http_archive(
        name = "rules_foreign_cc",
        urls = [
            "https://github.com/bazelbuild/rules_foreign_cc/archive/refs/heads/main.tar.gz",
        ],
        strip_prefix = "rules_foreign_cc-main",
    )

    http_archive(
        name = "rules_m4",
        urls = [
            "https://github.com/jmillikin/rules_m4/archive/refs/heads/trunk.tar.gz",
        ],
        strip_prefix = "rules_m4-trunk",
    )

    http_archive(
        name = "rules_proto",
        urls = [
            "https://github.com/bazelbuild/rules_proto/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "rules_proto-master",
    )

    http_archive(
        name = "com_github_apache_thrift",
        urls = [
            "https://github.com/apache/thrift/archive/refs/heads/master.tar.gz",
        ],
        strip_prefix = "thrift-master",
        build_file = "@com_curoky_tame//:recipes/t/thrift/default/BUILD",
    )

    http_archive(
        name = "com_github_facebook_wangle",
        urls = [
            "https://github.com/facebook/wangle/archive/refs/tags/v2022.04.25.00.tar.gz",
        ],
        strip_prefix = "wangle-2022.04.25.00",
        build_file = "@com_curoky_tame//:recipes/w/wangle/default/BUILD",
    )
