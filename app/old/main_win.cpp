#include "main_win.h"

namespace deeznes {
namespace app {

main_win::main_win()
    : m_win("Deeznes", 100, 100, 640, 480, SDL_WINDOW_SHOWN),
      m_renderer(m_win.get(), -1,
                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) {}

void main_win::render() {
    m_renderer.clear();
    m_renderer.present();
}

} // namespace app
} // namespace deeznes