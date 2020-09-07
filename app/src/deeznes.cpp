#include <boost/format.hpp>
#include <boost/scope_exit.hpp>
#include <console/nes_console.h>
#include <iostream>
#include <sdlpp/sdl_context.h>
#include <sdlpp/sdl_renderer.h>
#include <sdlpp/sdl_surface.h>
#include <sdlpp/sdl_texture.h>
#include <sdlpp/sdl_window.h>

using namespace deeznes::console;
using namespace deeznes::sdlpp;
using boost::format;

int main(int argc, char *argv[]) {
  try {
    if (argc != 2) {
      throw std::runtime_error((format("Usage: %1% rom.nes") % argv[0]).str());
    }

    sdl_context ctxt(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    sdl_window win("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    sdl_renderer renderer = win.create_renderer(
        -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    nes_console c;
    c.insert_cart(argv[1]);
    c.power_on();

    while (1) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          return 0;
        } else if (event.type == SDL_KEYDOWN) {
          switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
          case SDLK_q:
            return 0;
          }
        }
      }

      renderer.clear();
      renderer.present();

      std::cout << c << '\n';
      c.run(1);
    }

    return 0;
  } catch (std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}