#pragma once

#include <console/nes_console.h>
#include <SFML/Graphics.hpp>
#include <boost/circular_buffer.hpp>
#include <string>

namespace deeznes {
namespace app {

class instr_display : public sf::Drawable, public sf::Transformable {
  private:
    deeznes::console::nes_console& m_console;
    sf::Font m_font;
    boost::circular_buffer<std::string> m_lines;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  public:
    instr_display(deeznes::console::nes_console& console);

    void update();
};

} // namespace app
} // namespace deeznes