#include "instr_display.h"
#include <boost/format.hpp>

namespace console = deeznes::console;

namespace deeznes {
namespace app {

instr_display::instr_display(deeznes::console::nes_console& console)
    : m_console(console)
{
    if (!m_font.loadFromFile("fonts/CascadiaCode.ttf"))
    {
        throw std::runtime_error("Could not load fonts/CascadiaCode.ttf");
    }
}

void instr_display::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

} // namespace app
} // namespace deeznes