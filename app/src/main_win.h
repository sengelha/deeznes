#pragma once

#include "window.h"
#include <sdlpp/sdlpp.h>

namespace deeznes {
namespace app {

class main_win : public window {
  private:
    deeznes::sdlpp::window m_win;
    deeznes::sdlpp::renderer m_renderer;

  public:
    main_win();
    void render();
};

} // namespace app
} // namespace deeznes