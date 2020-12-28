cc_library(
    name = "cpu",
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["include/cpu/*.h"]),
    include_prefix = "cpu",
    strip_include_prefix = "include/cpu",
    visibility = ["//visibility:public"],
    deps = [
        "@boost//:assert",
        "@boost//:format",
    ],
)

cc_test(
    name = "cpu_tests",
    srcs = [
        "test/fuzz_tests.cpp",
        "test/nonstd_instr.cpp",
        "test/state_tests.cpp",
        "test/std_instr.cpp",
        "test/test_mem.h",
    ],
    deps = [
        ":cpu",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
