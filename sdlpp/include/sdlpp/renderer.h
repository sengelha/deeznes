#pragma once

#include "surface.h"
#include "texture.h"
#include <SDL2/SDL.h>
#include <boost/format.hpp>
#include <stdexcept>

namespace deeznes {
namespace sdlpp {

class renderer : private boost::noncopyable {
  private:
    SDL_Renderer *ren_;

  public:
    renderer(SDL_Window *win, int index, Uint32 flags);
    renderer(renderer &&other);

    SDL_Renderer *get() const noexcept { return ren_; }

    void clear() { SDL_RenderClear(ren_); }

    void copy(const texture &texture, const SDL_Rect *srcrect,
              const SDL_Rect *dstrect) {
        SDL_RenderCopy(ren_, texture.get(), srcrect, dstrect);
    }

    void present() { SDL_RenderPresent(ren_); }

    texture create_texture_from_surface(const surface &surface) {
        return texture(ren_, surface.get());
    }

    ~renderer() { SDL_DestroyRenderer(ren_); }
};

} // namespace sdlpp
} // namespace deeznes