default_copts = select({
    "@platforms//os:windows": ["/std:c++17"],
    "//conditions:default": ["-std=c++17"],
})

cc_library(
    name = "console",
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["include/console/*.h"]),
    copts = default_copts,
    include_prefix = "console",
    strip_include_prefix = "include/console",
    visibility = ["//visibility:public"],
    deps = [
        "//cart",
        "//cpu",
        "//io",
        "//ppu",
    ],
)

cc_test(
    name = "console_tests",
    srcs = glob(["test/*.cpp"]),
    copts = default_copts,
    data = [
        "//roms:nestest.log",
        "//roms:nestest.nes",
    ],
    deps = [
        ":console",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
