load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake_external(
    name = "sfml",
    cache_entries = {
        "SFML_DEPENDENCIES_INSTALL_PREFIX": ".",
        "SFML_MISC_INSTALL_PREFIX": ".",
    },
    lib_source = ":all",
    shared_libraries = select({
        "@platforms//os:osx": [
            "libsfml-audio.2.5.dylib",
            "libsfml-graphics.2.5.dylib",
            "libsfml-network.2.5.dylib",
            "libsfml-system.2.5.dylib",
            "libsfml-window.2.5.dylib",
        ],
        "@platforms//os:linux": [
            "libsfml-audio.so.2.5",
            "libsfml-graphics.so.2.5",
            "libsfml-network.so.2.5",
            "libsfml-system.so.2.5",
            "libsfml-window.so.2.5",
        ]
    }),
    visibility = ["//visibility:public"],
)

# TODO: Import frameworks and reference them from