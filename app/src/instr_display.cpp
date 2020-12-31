#include "instr_display.h"
#include <boost/format.hpp>
#include <sstream>

namespace console = deeznes::console;

namespace deeznes {
namespace app {

instr_display::instr_display(deeznes::console::nes_console &console)
    : m_console(console), m_lines(10) {
    if (!m_font.loadFromFile("fonts/CascadiaCode.ttf")) {
        throw std::runtime_error("Could not load fonts/CascadiaCode.ttf");
    }
}

void instr_display::update() {
    std::stringstream ss;
    ss << m_console;
    m_lines.push_back(ss.str());
}

void instr_display::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
    states.transform *= getTransform();

    int y = 0;
    for (auto line : m_lines) {
        sf::Text text;
        text.setFont(m_font);
        text.setString(line);
        text.setCharacterSize(14);
        text.setPosition(0, y);
        target.draw(text, states);

        y += 16;
    }
}

} // namespace app
} // namespace deeznes