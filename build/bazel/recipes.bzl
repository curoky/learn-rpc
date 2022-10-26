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

def deps_tools():
    http_archive(
        name = "hedron_compile_commands",
        urls = ["https://github.com/hedronvision/bazel-compile-commands-extractor/archive/refs/heads/main.tar.gz"],
        strip_prefix = "bazel-compile-commands-extractor-main",
    )

    http_archive(
        name = "rules_bison",
        urls = ["https://github.com/jmillikin/rules_bison/archive/refs/tags/v0.2.tar.gz"],
        strip_prefix = "rules_bison-0.2",
        patch_cmds = ["sed -i '83d' bison/bison.bzl"],
    )

    http_archive(
        name = "com_github_nelhage_rules_boost",
        urls = ["https://github.com/nelhage/rules_boost/archive/refs/heads/master.tar.gz"],
        strip_prefix = "rules_boost-master",
    )

    http_archive(
        name = "rules_flex",
        urls = ["https://github.com/jmillikin/rules_flex/archive/refs/tags/v0.2.tar.gz"],
        strip_prefix = "rules_flex-0.2",
        patch_cmds = ["sed -i '76d' flex/flex.bzl"],
    )

    http_archive(
        name = "rules_m4",
        urls = ["https://github.com/jmillikin/rules_m4/archive/refs/heads/trunk.tar.gz"],
        strip_prefix = "rules_m4-trunk",
    )

    http_archive(
        name = "rules_proto",
        urls = ["https://github.com/bazelbuild/rules_proto/archive/refs/heads/master.tar.gz"],
        strip_prefix = "rules_proto-master",
    )

def deps_libs():
    http_archive(
        name = "com_google_absl",
        urls = ["https://github.com/abseil/abseil-cpp/archive/refs/tags/20220623.1.tar.gz"],
        strip_prefix = "abseil-cpp-20220623.1",
    )

    http_archive(
        name = "com_googlesource_code_re2",
        urls = ["https://github.com/google/re2/archive/refs/tags/2022-06-01.tar.gz"],
        strip_prefix = "re2-2022-06-01",
    )

    http_archive(
        name = "com_github_google_brotli",
        urls = ["https://github.com/google/brotli/archive/refs/heads/master.tar.gz"],
        strip_prefix = "brotli-master",
    )

    # http_archive(
    #     name = "com_github_nlohmann_json",
    #     urls = ["https://github.com/nlohmann/json/archive/refs/tags/v3.11.2.tar.gz"],
    #     strip_prefix = "json-3.11.2",
    # )

    http_archive(
        name = "com_github_google_double_conversion",
        urls = ["https://github.com/google/double-conversion/archive/refs/tags/v3.2.1.tar.gz"],
        patch_cmds = ["sed -i -e 's/linkopts/includes = [\".\"],linkopts/g' BUILD"],
        strip_prefix = "double-conversion-3.2.1",
    )

    http_archive(
        name = "com_github_google_flatbuffers",
        urls = ["https://github.com/google/flatbuffers/archive/refs/tags/v22.10.26.tar.gz"],
        strip_prefix = "flatbuffers-22.10.26",
    )

    http_archive(
        name = "com_github_fmtlib_fmt",
        urls = ["https://github.com/fmtlib/fmt/archive/refs/tags/8.1.1.tar.gz"],
        strip_prefix = "fmt-8.1.1",
        patch_cmds = ["mv support/bazel/BUILD.bazel BUILD.bazel"],
    )

    http_archive(
        name = "com_github_catchorg_catch2",
        urls = ["https://github.com/catchorg/Catch2/archive/refs/heads/devel.tar.gz"],
        strip_prefix = "Catch2-devel",
    )

    http_archive(
        name = "com_github_gflags_gflags",
        urls = ["https://github.com/gflags/gflags/archive/refs/heads/master.tar.gz"],
        strip_prefix = "gflags-master",
    )

    http_archive(
        name = "com_github_google_glog",
        urls = ["https://github.com/google/glog/archive/refs/tags/v0.5.0.tar.gz"],
        strip_prefix = "glog-0.5.0",
    )

    http_archive(
        name = "com_github_google_googletest",
        urls = ["https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz"],
        strip_prefix = "googletest-release-1.12.1",
    )
    http_archive(
        name = "com_google_protobuf",
        urls = ["https://github.com/protocolbuffers/protobuf/archive/refs/tags/v3.19.4.tar.gz"],
        strip_prefix = "protobuf-3.19.4",
        patch_cmds = ["sed -i -e 's/@zlib/@net_zlib_zlib/g' BUILD"],
    )

    # http_archive(
    #     name = "com_pagure_libaio",
    #     urls = ["https://pagure.io/libaio/archive/libaio-0.3.113/libaio-libaio-0.3.113.tar.gz"],
    #     strip_prefix = "libaio-libaio-0.3.113",
    #     build_file = "@com_curoky_tame//:recipes/l/libaio/default/BUILD",
    # )

    http_archive(
        name = "com_github_facebook_fatal",
        urls = ["https://github.com/facebook/fatal/archive/refs/tags/v2022.10.17.00.tar.gz"],
        strip_prefix = "fatal-2022.10.17.00",
        build_file = "//:build/bazel/fatal.BUILD",
    )

    http_archive(
        name = "com_github_facebookincubator_fizz",
        urls = ["https://github.com/facebookincubator/fizz/archive/refs/tags/v2022.10.17.00.tar.gz"],
        strip_prefix = "fizz-2022.10.17.00",
        build_file = "//:build/bazel/fizz.BUILD",
    )

    http_archive(
        name = "com_github_facebook_proxygen",
        urls = ["https://github.com/facebook/proxygen/archive/refs/tags/v2022.10.17.00.tar.gz"],
        strip_prefix = "proxygen-2022.10.17.00",
        build_file = "//:build/bazel/proxygen.BUILD",
    )

def pkg_rules_dependencies():
    deps_libs()
    deps_tools()
