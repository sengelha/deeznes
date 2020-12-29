load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Begin boost
git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "fbac9be7640ecc0fab075233d394f08f1a37e449",
    remote = "https://github.com/nelhage/rules_boost",
    shallow_since = "1606155806 -0800",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")

boost_deps()
# End boost

# Begin rules_foreign_cc
http_archive(
    name = "rules_foreign_cc",
    sha256 = "3c6445404e9e5d17fa0ecdef61be00dd93b20222c11f45e146a98c0a3f67defa",
    strip_prefix = "rules_foreign_cc-d54c78ab86b40770ee19f0949db9d74a831ab9f0",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/d54c78ab86b40770ee19f0949db9d74a831ab9f0.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()
# End rules_foreign_cc

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
    build_file = "third_party/sfml.BUILD",
    sha256 = "bf1e0643acb92369b24572b703473af60bac82caf5af61e77c063b779471bb7f",
    strip_prefix = "SFML-2.5.1",
    url = "https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip",
)
# End SFML
