#pragma once

#include <SDL2/SDL.h>
#include <boost/core/noncopyable.hpp>
#include <boost/format.hpp>
#include <stdexcept>

namespace deeznes {
namespace sdlpp {

class texture : private boost::noncopyable {
  private:
    SDL_Texture *t_;

  public:
    texture(SDL_Renderer *renderer, SDL_Surface *surface);
    texture(texture &&other);
    ~texture();

    SDL_Texture *get() const noexcept { return t_; }
};

} // namespace sdlpp
} // namespace deeznes