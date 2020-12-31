load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Begin boost
git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "fbac9be7640ecc0fab075233d394f08f1a37e449",
    remote = "https://github.com/nelhage/rules_boost",
    shallow_since = "1606155806 -0800",
)

http_archive(
    name = "boost",
    build_file = "@com_github_nelhage_rules_boost//:BUILD.boost",
    patch_cmds = ["rm -f doc/pdf/BUILD"],
    sha256 = "aeb26f80e80945e82ee93e5939baebdca47b9dee80a07d3144be1e1a6a66dd6a",
    strip_prefix = "boost_1_75_0",
    urls = [
        "https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.gz",
    ],
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")

boost_deps()
# End boost

# Begin gtest
http_archive(
    name = "gtest",
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
    strip_prefix = "googletest-release-1.10.0",
    url = "https://github.com/google/googletest/archive/release-1.10.0.zip",
)
# End gtest

# Begin SFML
http_archive(
    name = "sfml",
    build_file = "sfml.BUILD",
    sha256 = "bf1e0643acb92369b24572b703473af60bac82caf5af61e77c063b779471bb7f",
    strip_prefix = "SFML-2.5.1",
    url = "https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip",
)
# End SFML
