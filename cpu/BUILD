cc_library(
    name = 'deeznescpu',
    srcs = glob(['src/*.cpp', 'src/*.h']),
    hdrs = glob(['include/*.h']),
    include_prefix = "cpu",
    strip_include_prefix = "include"
)

cc_test(
    name = 'test',
    srcs = glob(['test/*.cpp', 'test/*.h']),
    deps = [
        "@gtest//:gtest",
        ":deeznescpu",
    ],
)