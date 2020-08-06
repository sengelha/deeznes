cc_library(
    name = 'console',
    srcs = glob(['src/*.cpp', 'src/*.h']),
    hdrs = glob(['include/*.h']),
    copts = ['-std=c++17'],
    deps = [
        "//cart",
        "//compat",
        "//cpu",
        "//io",
        "//ppu",
    ],
    include_prefix = "console",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_test(
    name = 'test',
    srcs = glob(['test/*.cpp', 'test/*.h']),
    copts = ['-std=c++17'],
    deps = [
        "@gtest//:gtest",
        ":console",
    ],
    data = [
        "//roms:nestest.log",
        "//roms:nestest.nes",
    ]
)