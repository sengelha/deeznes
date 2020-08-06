cc_library(
    name = 'ppu',
    srcs = glob(['src/*.cpp', 'src/*.h']),
    hdrs = glob(['include/*.h']),
    include_prefix = "ppu",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_test(
    name = 'test',
    srcs = glob(['test/*.cpp', 'test/*.h']),
    deps = [
        "@gtest//:gtest",
        ":ppu",
    ],
)