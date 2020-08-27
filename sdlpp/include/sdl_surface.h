#pragma once

#include <SDL2/SDL.h>
#include <boost/format.hpp>
#include <sdlpp/non_copyable.h>
#include <stdexcept>

namespace deeznes {
namespace sdlpp {

class sdl_surface : non_copyable {
private:
  SDL_Surface *s_;

  sdl_surface(SDL_Surface *s) : s_(s) {}

public:
  static sdl_surface load_bmp(const char *file) {
    SDL_Surface *s = SDL_LoadBMP(file);
    if (s == nullptr) {
      throw std::runtime_error(
          (boost::format("Unable to create surface: %1%") % SDL_GetError())
              .str());
    }
    return sdl_surface(s);
  }

  SDL_Surface *get() const noexcept { return s_; }

  void free() {
    if (s_ != nullptr) {
      SDL_FreeSurface(s_);
      s_ = nullptr;
    }
  }

  ~sdl_surface() { free(); }
};

} // namespace sdlpp
} // namespace deeznes