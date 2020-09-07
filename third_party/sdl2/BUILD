cc_import(
    name = "libsdl2_import",
    interface_library = "lib/x64/SDL2.lib",
    shared_library = "lib/x64/SDL2.dll",
)

cc_library(
    name = "libsdl2",
    hdrs = glob(["include/*.h"]),
    strip_include_prefix = "include",
    include_prefix = "SDL2",
    deps = ["libsdl2_import"],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "libsdl2main",
    static_library = "lib/x64/SDL2main.lib",
    visibility = ["//visibility:public"],
)