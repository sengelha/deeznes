cc_library(
    name = "lib",
    deps = select({
        "@bazel_tools//src/conditions:darwin": ["@sdl2mac//:lib"],
        "@bazel_tools//src/conditions:linux_x86_64": ["@sdl2linux//:lib"],
    }),
    visibility = ["//visibility:public"],
)