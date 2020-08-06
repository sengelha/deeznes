cc_library(
    name = 'sdlpp',
    srcs = glob(['src/*.cpp', 'src/*.h']),
    hdrs = glob(['include/*.h']),
    deps = [
        "@sdl2//:sdl2",
    ],
    include_prefix = "sdlpp",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)