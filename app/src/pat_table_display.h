#pragma once

#include <console/nes_console.h>
#include <SFML/Graphics.hpp>

namespace deeznes {
namespace app {

class pat_table_display : public sf::Drawable, public sf::Transformable {
  private:
    deeznes::console::nes_console& console_;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  public:
    pat_table_display(deeznes::console::nes_console& console);
};

} // namespace app
} // namespace deeznes