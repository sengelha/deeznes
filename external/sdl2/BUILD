cc_library(
    name = "libSDL2",
    deps = select({
        "@bazel_tools//src/conditions:darwin": ["@sdl2mac//:libSDL2"],
        "@bazel_tools//src/conditions:linux_x86_64": ["@sdl2linux//:libSDL2"],
    }),
    visibility = ["//visibility:public"],
)