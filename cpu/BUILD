cc_library(
    name = 'cpu',
    srcs = glob(['src/*.cpp', 'src/*.h']),
    hdrs = glob(['include/*.h']),
    copts = select({
      "@bazel_tools//src/conditions:windows": [
        "/permissive-",
        "/W4",
        "/w14640",
      ],
    }),
    deps = [
        "@boost//:assert",
        "@boost//:format",
    ],
    include_prefix = "cpu",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_test(
    name = 'test',
    srcs = glob(['test/*.cpp', 'test/*.h']),
    deps = [
        "@gtest//:gtest",
        ":cpu",
    ],
)