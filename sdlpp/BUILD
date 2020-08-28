cc_library(
    name = 'sdlpp',
    srcs = glob(['src/*.cpp', 'src/*.h']),
    hdrs = glob(['include/*.h']),
    deps = ["//external/sdl2:lib"],
    include_prefix = "sdlpp",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)