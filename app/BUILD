SDL_LINKOPTS = select({
    "@bazel_tools//src/conditions:windows": [
        "-DEFAULTLIB:user32",
        "-DEFAULTLIB:gdi32",
        "-DEFAULTLIB:winmm",
        "-DEFAULTLIB:imm32",
        "-DEFAULTLIB:ole32",
        "-DEFAULTLIB:oleaut32",
        "-DEFAULTLIB:version",
        "-DEFAULTLIB:uuid",
        "-DEFAULTLIB:shell32",
        "-DEFAULTLIB:advapi32",
        "-DEFAULTLIB:hid",
        "-DEFAULTLIB:setupapi",
        "-DEFAULTLIB:opengl32",
        "-DEFAULTLIB:kernel32",
    ],
    "//conditions:default": [],
})

cc_binary(
    name = "app",
    srcs = glob([
        "src/*.cpp",
        "src/*.h",
    ]),
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++17"],
    }),
    linkopts = SDL_LINKOPTS,
    deps = [
        "//console",
        "//sdlpp",
        "//sdlttfpp",
        "@boost//:format",
    ],
)
