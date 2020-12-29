#pragma once

#include "window.h"
#include <console/nes_console.h>
#include <sdlpp/sdlpp.h>

namespace deeznes {
namespace app {

class cpu_win : public window {
  private:
    deeznes::console::nes_console *m_console;
    deeznes::sdlpp::window m_win;
    deeznes::sdlpp::renderer m_renderer;

  public:
    cpu_win(deeznes::console::nes_console *console, int x, int y, int w, int h);
    void render();
};

} // namespace app
} // namespace deeznes