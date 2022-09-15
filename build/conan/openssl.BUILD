load("@rules_cc//cc:defs.bzl", "cc_import", "cc_library")

cc_import(
    name = "ssl_precompiled",
    static_library = "lib/libssl.a",
)

cc_import(
    name = "crypto_precompiled",
    static_library = "lib/libcrypto.a",
)

cc_library(
    name = "openssl",
    hdrs = glob(["include/**"]),
    includes = ["include"],
    linkopts = [
        "-ldl",
        "-lpthread",
        "-lrt",
    ],
    visibility = ["//visibility:public"],
    deps = [
        # do not sort
        ":ssl_precompiled",
        ":crypto_precompiled",
    ],
)

cc_library(
    name = "ssl",
    hdrs = glob(["include/**"]),
    includes = ["include"],
    linkopts = [
        "-ldl",
        "-lpthread",
        "-lrt",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":ssl_precompiled",
    ],
)

cc_library(
    name = "crypto",
    hdrs = glob(["include/**"]),
    includes = ["include"],
    linkopts = [
        "-ldl",
        "-lpthread",
        "-lrt",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":crypto_precompiled",
    ],
)
