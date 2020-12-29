#pragma once

#include <console/nes_console.h>
#include <SFML/Graphics.hpp>

namespace deeznes {
namespace app {

class instr_display : public sf::Drawable, public sf::Transformable {
  private:
    deeznes::console::nes_console& m_console;
    sf::Font m_font;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  public:
    instr_display(deeznes::console::nes_console& console);
};

} // namespace app
} // namespace deeznes