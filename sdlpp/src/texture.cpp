#include <sdlpp/texture.h>

namespace deeznes {
namespace sdlpp {

texture::texture(SDL_Renderer *renderer, SDL_Surface *surface) {
    t_ = SDL_CreateTextureFromSurface(renderer, surface);
    if (t_ == nullptr) {
        throw std::runtime_error(
            (boost::format("Unable to create texture from surface: %1%") %
             SDL_GetError())
                .str());
    }
}

texture::texture(texture &&other) {
    t_ = other.t_;
    other.t_ = nullptr;
}

texture::~texture() {
    if (t_ != nullptr) {
        SDL_DestroyTexture(t_);
    }
}

} // namespace sdlpp
} // namespace deeznes