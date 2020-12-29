#include "cpu_display.h"
#include <boost/format.hpp>

namespace console = deeznes::console;

namespace deeznes {
namespace app {

cpu_display::cpu_display(deeznes::console::nes_console& console)
    : m_console(console)
{
    if (!m_font.loadFromFile("fonts/CascadiaCode.ttf"))
    {
        throw std::runtime_error("Could not load fonts/CascadiaCode.ttf");
    }
}

void cpu_display::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    auto state = m_console.state();

    std::vector<boost::format> lines;
    lines.push_back(boost::format("A: $%02X") % (int)state.cpu_state.regs.A);
    lines.push_back(boost::format("X: $%02X") % (int)state.cpu_state.regs.X);
    lines.push_back(boost::format("Y: $%02X") % (int)state.cpu_state.regs.Y);
    lines.push_back(boost::format("P: $%02X") % (int)state.cpu_state.regs.P);
    lines.push_back(boost::format("S: $%02X") % (int)state.cpu_state.regs.S);
    lines.push_back(boost::format("PC: $%04X") % (int)state.cpu_state.regs.PC);
    lines.push_back(boost::format("CYC: %d") % (int)state.cpu_state.cycles);

    int y = 0;
    for (auto line : lines)
    {
        sf::Text text;
        text.setFont(m_font);
        text.setString(line.str());
        text.setCharacterSize(24);
        text.setPosition(0, y);
        target.draw(text, states);

        y += 30;
    }
}

} // namespace app
} // namespace deeznes