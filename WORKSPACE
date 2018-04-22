# Copyright 2021 curoky(cccuroky@gmail.com).
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

workspace(name = "com_github_curoky_carrier")

# load("@//:builddir/conan/dependencies.bzl", "load_conan_dependencies")
# load_conan_dependencies()

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "com_curoky_tame",
    branch = "master",
    remote = "https://github.com/curoky/tame",
)

# local_repository(
#     name = "com_curoky_rules_pkg",
#     path = "/home/curoky/repos/cpp/rules_pkg",
# )

load("@com_github_curoky_my_own_x//config/bazel:recipes.bzl", "pkg_rules_dependencies")

pkg_rules_dependencies(["qt"])

load("@//:builddir/conan/dependencies.bzl", "load_conan_dependencies")
load_conan_dependencies()

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

# load("//build/bazel/register_toolchains.bzl", "pkg_register_toolchains")

# pkg_register_toolchains()

load("@rules_bison//bison:bison.bzl", "bison_register_toolchains")
load("@rules_flex//flex:flex.bzl", "flex_register_toolchains")
load("@rules_m4//m4:m4.bzl", "m4_register_toolchains")
load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")


m4_register_toolchains()

flex_register_toolchains()

bison_register_toolchains()

rules_foreign_cc_dependencies()

hedron_compile_commands_setup()

bazel_skylib_workspace()

protobuf_deps()

rules_proto_dependencies()

rules_proto_toolchains()
