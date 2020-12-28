cc_library(
    name = "ppu",
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["include/ppu/*.h"]),
    include_prefix = "ppu",
    strip_include_prefix = "include/ppu",
    visibility = ["//visibility:public"],
)

cc_test(
    name = "ppu_tests",
    srcs = [
        "test/basics.cpp",
    ],
    deps = [
        ":ppu",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
