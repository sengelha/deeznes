load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# Begin gtest
http_archive(
    name = "gtest",
    # Latest as of 2020-08-04
    url = "https://github.com/google/googletest/archive/release-1.10.0.tar.gz",
    sha256 = "9dc9157a9a1551ec7a7e43daea9a694a0bb5fb8bec81235d8a1e6ef64c716dcb",
    strip_prefix = "googletest-release-1.10.0",
)
# End gtest

# Begin sdl2
http_archive(
    name = "sdl2",
    # Latest as of 2020-09-06
    url = "https://github.com/bazelregistry/sdl2/archive/4199cadf3342666c49760541c738dc7db9aaa8b3.zip",
    sha256 = "b20432c3771af22af119134b546354ae4a0ebe62eaa05e2a0d1be2c6eaf80f0f",
    strip_prefix = "sdl2-4199cadf3342666c49760541c738dc7db9aaa8b3",
)
# End sdl2

# Begin freetype
http_archive(
    name = "freetype",
    url = "https://download.savannah.gnu.org/releases/freetype/freetype-2.10.2.tar.gz",
    sha256 = "e09aa914e4f7a5d723ac381420949c55c0b90b15744adce5d1406046022186ab",
    strip_prefix = "freetype-2.10.2",
    build_file = "@//external/freetype:freetype.BUILD"
)
# End freetype

# Begin sdl2ttf
http_archive(
    name = "sdl2ttf",
    url = "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz",
    sha256 = "a9eceb1ad88c1f1545cd7bd28e7cbc0b2c14191d40238f531a15b01b1b22cd33",
    strip_prefix = "SDL2_ttf-2.0.15",
    build_file = "@//external/sdl2ttf:sdl2ttf.BUILD"
)
# End sdl2ttf

# Begin boost
git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "1e3a69bf2d5cd10c34b74f066054cd335d033d71",
    remote = "https://github.com/nelhage/rules_boost",
    shallow_since = "1591047380 -0700",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()
# End boost