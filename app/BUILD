default_copts = select({
    "@platforms//os:windows": ["/std:c++17"],
    "//conditions:default": ["-std=c++17"],
})

cc_binary(
    name = "app",
    srcs = glob([
        "src/*.cpp",
        "src/*.h",
    ]),
    copts = default_copts,
    deps = [
        "//console",
        "@boost//:circular_buffer",
        "@sfml//:sfml",
    ],
    data = [
        "//fonts:CascadiaCode.ttf",
    ],
)
