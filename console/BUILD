cc_library(
    name = 'deeznesconsole',
    srcs = glob(['src/*.cpp', 'src/*.h']),
    hdrs = glob(['include/*.h']),
    include_prefix = "console",
    strip_include_prefix = "include",
    deps = [
        "//cart:deeznescart"
        "//cpu:deeznescpu"
    ]
)

cc_test(
    name = 'test',
    srcs = glob(['test/*.cpp', 'test/*.h']),
    deps = [
        "@gtest//:gtest",
        ":deeznesconsole",
    ],
)