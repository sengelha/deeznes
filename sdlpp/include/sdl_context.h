#pragma once

#include <SDL2/SDL.h>
#include <boost/format.hpp>
#include <sdlpp/non_copyable.h>
#include <stdexcept>

namespace deeznes {
namespace sdlpp {

class sdl_context : non_copyable {
public:
  sdl_context(Uint32 flags) {
    if (SDL_Init(flags) != 0) {
      throw std::runtime_error(
          (boost::format("Unable to initialize SDL: %1%") % SDL_GetError())
              .str());
    }
  }

  ~sdl_context() { SDL_Quit(); }
};

} // namespace sdlpp
} // namespace deeznes