load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

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

# Begin rules_sfml
git_repository(
    name = "com_github_sengelha_rules_sfml",
    commit = "d13eac5ed8ba6f6058f1fcf144103ac6d795ba52",
    remote = "https://github.com/sengelha/rules_sfml",
    shallow_since = "1609535242 -0600",
)

load("@com_github_sengelha_rules_sfml//sfml:deps.bzl", "rules_sfml_deps")

rules_sfml_deps()

load("@com_github_sengelha_rules_sfml//sfml:sfml.bzl", "rules_sfml_setup")

rules_sfml_setup()
# End rules_sfml

# Begin gtest
http_archive(
    name = "gtest",
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
    strip_prefix = "googletest-release-1.10.0",
    url = "https://github.com/google/googletest/archive/release-1.10.0.zip",
)
# End gtest
