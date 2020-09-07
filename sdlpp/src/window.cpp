#include <sdlpp/window.h>

namespace deeznes {
namespace sdlpp {

window::window(const char *title, int x, int y, int w, int h, Uint32 flags) {
    win_ = SDL_CreateWindow(title, x, y, w, h, flags);
    if (win_ == nullptr) {
        throw std::runtime_error(
            (boost::format("Unable to create window: %1%") % SDL_GetError())
                .str());
    }
}

} // namespace sdlpp
} // namespace deeznes