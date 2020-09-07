#include <sdlpp/renderer.h>

namespace deeznes {
namespace sdlpp {

renderer::renderer(SDL_Window *win, int index, Uint32 flags) {
    ren_ = SDL_CreateRenderer(win, index, flags);
    if (ren_ == nullptr) {
        throw std::runtime_error(
            (boost::format("Unable to create renderer: %1%") % SDL_GetError())
                .str());
    }
}

} // namespace sdlpp
} // namespace deeznes