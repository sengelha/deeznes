load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "gtest",
    # Latest as of 2020-08-04
    url = "https://github.com/google/googletest/archive/release-1.10.0.tar.gz",
    sha256 = "9dc9157a9a1551ec7a7e43daea9a694a0bb5fb8bec81235d8a1e6ef64c716dcb",
    strip_prefix = "googletest-release-1.10.0",
)

new_local_repository(
    name = "sdl2linux",
    path = "/usr/lib/x86_64-linux-gnu",
    build_file = "@//external/sdl2:sdl2.BUILD"
)

new_local_repository(
    name = "sdl2mac",
    path = "/usr/local/lib",
    build_file = "@//external/sdl2:sdl2.BUILD"
)


# http_archive(
#     name = "sdl2",
#     url = "https://www.libsdl.org/release/SDL2-2.0.12.tar.gz",
#     sha256 = "349268f695c02efbc9b9148a70b85e58cefbbf704abd3e91be654db7f1e2c863",
#     build_file = "@//external:sdl2.BUILD",
#     strip_prefix = "SDL2-2.0.12",
# )