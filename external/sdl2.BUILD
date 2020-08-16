SDL2_HEADERS=[
    "include/SDL2/SDL.h",
    "include/SDL2/SDL_assert.h",
    "include/SDL2/SDL_atomic.h",
    "include/SDL2/SDL_audio.h",
    "include/SDL2/SDL_bits.h",
    "include/SDL2/SDL_blendmode.h",
    "include/SDL2/SDL_clipboard.h",
    "include/SDL2/SDL_config.h",
    "include/SDL2/SDL_cpuinfo.h",
    "include/SDL2/SDL_egl.h",
    "include/SDL2/SDL_endian.h",
    "include/SDL2/SDL_error.h",
    "include/SDL2/SDL_events.h",
    "include/SDL2/SDL_filesystem.h",
    "include/SDL2/SDL_gamecontroller.h",
    "include/SDL2/SDL_gesture.h",
    "include/SDL2/SDL_haptic.h",
    "include/SDL2/SDL_hints.h",
    "include/SDL2/SDL_joystick.h",
    "include/SDL2/SDL_keyboard.h",
    "include/SDL2/SDL_keycode.h",
    "include/SDL2/SDL_loadso.h",
    "include/SDL2/SDL_log.h",
    "include/SDL2/SDL_main.h",
    "include/SDL2/SDL_messagebox.h",
    "include/SDL2/SDL_metal.h",
    "include/SDL2/SDL_mouse.h",
    "include/SDL2/SDL_mutex.h",
    "include/SDL2/SDL_name.h",
    "include/SDL2/SDL_opengl.h",
    "include/SDL2/SDL_opengl_glext.h",
    "include/SDL2/SDL_opengles.h",
    "include/SDL2/SDL_opengles2.h",
    "include/SDL2/SDL_opengles2_gl2.h",
    "include/SDL2/SDL_opengles2_gl2ext.h",
    "include/SDL2/SDL_opengles2_gl2platform.h",
    "include/SDL2/SDL_opengles2_khrplatform.h",
    "include/SDL2/SDL_pixels.h",
    "include/SDL2/SDL_platform.h",
    "include/SDL2/SDL_power.h",
    "include/SDL2/SDL_quit.h",
    "include/SDL2/SDL_rect.h",
    "include/SDL2/SDL_render.h",
    "include/SDL2/SDL_revision.h",
    "include/SDL2/SDL_rwops.h",
    "include/SDL2/SDL_scancode.h",
    "include/SDL2/SDL_sensor.h",
    "include/SDL2/SDL_shape.h",
    "include/SDL2/SDL_stdinc.h",
    "include/SDL2/SDL_surface.h",
    "include/SDL2/SDL_system.h",
    "include/SDL2/SDL_syswm.h",
    "include/SDL2/SDL_test.h",
    "include/SDL2/SDL_test_assert.h",
    "include/SDL2/SDL_test_common.h",
    "include/SDL2/SDL_test_compare.h",
    "include/SDL2/SDL_test_crc32.h",
    "include/SDL2/SDL_test_font.h",
    "include/SDL2/SDL_test_fuzzer.h",
    "include/SDL2/SDL_test_harness.h",
    "include/SDL2/SDL_test_images.h",
    "include/SDL2/SDL_test_log.h",  
    "include/SDL2/SDL_test_md5.h",
    "include/SDL2/SDL_test_memory.h",
    "include/SDL2/SDL_test_random.h",
    "include/SDL2/SDL_thread.h",
    "include/SDL2/SDL_timer.h",
    "include/SDL2/SDL_touch.h",
    "include/SDL2/SDL_types.h",
    "include/SDL2/SDL_version.h",
    "include/SDL2/SDL_video.h",
    "include/SDL2/SDL_vulkan.h",
    "include/SDL2/begin_code.h",
    "include/SDL2/close_code.h",
]

genrule(
    name = "build_sdl2",
    srcs = glob(["**"]),
    outs = ["sdl2.tar.gz"],
    cmd = """
TMP_DIR=`mktemp -d`
trap "rm -rf $$TMP_DIR" EXIT

pushd external/sdl2
./configure --prefix=$$TMP_DIR
make
make install
popd
tar -C $$TMP_DIR -czf $(location sdl2.tar.gz) .
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