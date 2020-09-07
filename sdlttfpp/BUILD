cc_library(
    name = "sdlttfpp",
    srcs = glob([
        "src/*.cpp",
        "src/*.h",
    ]),
    hdrs = glob(["include/*.h"]),
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
    }),
    include_prefix = "sdlttfpp",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        "//sdlpp",
        "@boost//:format",
        "@sdl2ttf",
    ],
)
