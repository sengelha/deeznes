cc_library(
    name = "compat",
    hdrs = glob(["include/compat/*.h"]),
    include_prefix = "compat",
    strip_include_prefix = "include/compat",
    visibility = ["//visibility:public"],
)

cc_test(
    name = "compat_tests",
    srcs = glob(["test/*.cpp"]),
    copts = select({
        "@platforms//os:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    deps = [
        ":compat",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
