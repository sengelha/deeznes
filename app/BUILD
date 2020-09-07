cc_binary(
    name = "app",
    srcs = glob(['src/*.cpp']),
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
    }),
    linkopts = [
        "shell32.lib",
    ],
    deps = [
        "//console",
        "//sdlpp",
        "//third_party/sdl2:libsdl2main",
        "@boost//:format",
    ],
)