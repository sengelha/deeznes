SDL2_HEADERS=["include/SDL2/SDL.h"]

genrule(
    name = "build_sdl2",
    srcs = glob(["**"]),
    outs = ["sdl2.tar.gz"],
    cmd = """
get_abs_filename() {
  echo "$$(cd "$$(dirname "$$1")" && pwd)/$$(basename "$$1")"
}

TMP_DIR=`mktemp -d`
trap "rm -rf $$TMP_DIR" EXIT

OUTPUT_TGZ=$$(get_abs_filename $(location sdl2.tar.gz))

cd external/sdl2
./configure --prefix=$$TMP_DIR
make -j
make install
tar -C $$TMP_DIR -czf $$OUTPUT_TGZ .
"""
)

genrule(
    name = "extract_built_sdl2",
    srcs = ["sdl2.tar.gz"],
    outs = ["lib/libSDL2.a"] + SDL2_HEADERS,
    cmd = """
tar -C $(@D) -zxf $(location sdl2.tar.gz)
"""
)

cc_import(
    name = "sdl2-private",
    hdrs = SDL2_HEADERS,
)

cc_library(
    name = "sdl2",
    hdrs = SDL2_HEADERS,
    includes = ["include"],
    deps = [":sdl2-private"],
    visibility = ["//visibility:public"],
)