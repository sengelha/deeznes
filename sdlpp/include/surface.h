#pragma once

#include <SDL.h>
#include <boost/core/noncopyable.hpp>
#include <boost/format.hpp>
#include <stdexcept>

namespace deeznes {
namespace sdlpp {

class surface : private boost::noncopyable {
  private:
    SDL_Surface *s_;

  public:
    surface(SDL_Surface *s) : s_(s) {}
    surface(surface &&other) {
        s_ = other.s_;
        other.s_ = nullptr;
    }

    static surface load_bmp(const char *file) {
        SDL_Surface *s = SDL_LoadBMP(file);
        if (s == nullptr) {
            throw std::runtime_error(
                (boost::format("Unable to create surface: %1%") %
                 SDL_GetError())
                    .str());
        }
        return surface(s);
    }

    SDL_Surface *get() const noexcept { return s_; }

    void free() {
        if (s_ != nullptr) {
            SDL_FreeSurface(s_);
            s_ = nullptr;
        }
    }

    ~surface() { free(); }
};

} // namespace sdlpp
} // namespace deeznes