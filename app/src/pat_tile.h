#pragma once

#include <console/nes_console.h>
#include <SFML/Graphics.hpp>

namespace deeznes {
namespace app {

class pat_tile : public sf::Drawable, public sf::Transformable {
  private:
    deeznes::console::nes_console& console_;
    int indx_;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  public:
    pat_tile(deeznes::console::nes_console& console, int indx);
};

} // namespace app
} // namespace deeznes