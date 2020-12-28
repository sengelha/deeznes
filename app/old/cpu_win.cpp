#include "cpu_win.h"
#include <boost/assert.hpp>
#include <sdlttfpp/sdlttfpp.h>
#include <sstream>

namespace console = deeznes::console;
namespace sdl = deeznes::sdlpp;
namespace sdlttf = deeznes::sdlttfpp;

namespace deeznes {
namespace app {

cpu_win::cpu_win(console::nes_console *console, int x, int y, int w, int h)
    : m_console(console), m_win("Deeznes CPU", x, y, w, h, SDL_WINDOW_SHOWN),
      m_renderer(m_win.get(), -1,
                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) {}

void cpu_win::render() {
    std::stringstream ss;
    ss << m_console->state().cpu_state;

    sdlttf::font font("C:\\windows\\fonts\\consola.ttf", 14);
    int w, h;
    std::tie(w, h) = font.size_text(ss.str());

    SDL_Color fg = {255, 255, 255};
    SDL_Color bg = {0, 0, 0};
    sdl::surface surface = font.render_text_shaded(ss.str(), fg, bg);
    sdl::texture texture = m_renderer.create_texture_from_surface(surface);

    m_renderer.clear();
    SDL_Rect rect = {0, 0, w, h};
    m_renderer.copy(texture, nullptr, &rect);
    m_renderer.present();
}

} // namespace app
} // namespace deeznes