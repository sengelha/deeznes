cc_library(
    name = "libc",
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["include/libc/*.h"]),
    include_prefix = "libc",
    strip_include_prefix = "include/libc",
    visibility = ["//visibility:public"],
    deps = [
        "@boost//:format",
    ],
)
