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
    deps = [
        ":compat",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
