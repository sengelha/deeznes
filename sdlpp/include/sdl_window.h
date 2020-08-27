#pragma once

#include <SDL2/SDL.h>
#include <boost/format.hpp>
#include <sdlpp/non_copyable.h>
#include <sdlpp/sdl_renderer.h>
#include <stdexcept>

namespace deeznes {
namespace sdlpp {

class sdl_window : non_copyable {
private:
  SDL_Window *win_;

public:
  sdl_window(const char *title, int x, int y, int w, int h, Uint32 flags) {
    win_ = SDL_CreateWindow(title, x, y, w, h, flags);
    if (win_ == nullptr) {
      throw std::runtime_error(
          (boost::format("Unable to create window: %1%") % SDL_GetError())
              .str());
    }
  }

  sdl_renderer create_renderer(int index, Uint32 flags) {
    return sdl_renderer(win_, index, flags);
  }

  ~sdl_window() { SDL_DestroyWindow(win_); }
};

} // namespace sdlpp
} // namespace deeznes