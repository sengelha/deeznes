#pragma once

#include <SDL2/SDL.h>
#include <boost/format.hpp>
#include <sdlpp/non_copyable.h>
#include <stdexcept>

namespace deeznes {
namespace sdlpp {

class sdl_texture : non_copyable {
private:
  SDL_Texture *t_;

public:
  sdl_texture(SDL_Renderer *renderer, SDL_Surface *surface) {
    t_ = SDL_CreateTextureFromSurface(renderer, surface);
    if (t_ == nullptr) {
      throw std::runtime_error(
          (boost::format("Unable to create texture from surface: %1%") %
           SDL_GetError())
              .str());
    }
  }

  SDL_Texture *get() const noexcept { return t_; }

  ~sdl_texture() { SDL_DestroyTexture(t_); }
};

} // namespace sdlpp
} // namespace deeznes