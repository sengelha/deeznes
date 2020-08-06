cc_library(
    name = 'deeznesconsole',
    srcs = glob(['src/*.cpp', 'src/*.h']),
    hdrs = glob(['include/*.h']),
    copts = ['-std=c++17'],
    include_prefix = "console",
    strip_include_prefix = "include",
    deps = [
        "//cart:deeznescart",
        "//compat:deeznescompat",
        "//cpu:deeznescpu",
        "//io:deeznesio",
        "//ppu:deeznesppu",
    ]
)

cc_test(
    name = 'test',
    srcs = glob(['test/*.cpp', 'test/*.h']),
    copts = ['-std=c++17'],
    deps = [
        "@gtest//:gtest",
        ":deeznesconsole",
    ],
    data = [
        "//roms:nestest.log",
        "//roms:nestest.nes",
    ]
)