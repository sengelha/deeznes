cc_library(
    name = "cart",
    srcs = glob([
        "src/*.cpp",
        "src/*.h",
    ]),
    hdrs = glob(["include/cart/*.h"]),
    copts = select({
        "@platforms//os:windows": ["/std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    include_prefix = "cart",
    strip_include_prefix = "include/cart",
    visibility = ["//visibility:public"],
    deps = [
        "//compat",
        "@boost//:format",
        "@boost//:iostreams",
    ],
)

cc_test(
    name = "cart_tests",
    srcs = glob(["test/*.cpp"]),
    data = [
        "//roms:donkey_kong.nes",
        "//roms:nestest.log",
        "//roms:nestest.nes",
    ],
    deps = [
        ":cart",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
