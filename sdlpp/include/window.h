#pragma once

#include "renderer.h"
#include <SDL.h>
#include <boost/format.hpp>
#include <stdexcept>

namespace deeznes {
namespace sdlpp {

class window : private boost::noncopyable {
  private:
    SDL_Window *win_;

  public:
    window(const char *title, int x, int y, int w, int h, Uint32 flags);

    SDL_Window *get() const noexcept { return win_; }

    renderer create_renderer(int index, Uint32 flags) {
        return renderer(win_, index, flags);
    }

    ~window() { SDL_DestroyWindow(win_); }
};

} // namespace sdlpp
} // namespace deeznes