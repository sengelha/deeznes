#include "pat_table_display.h"

namespace console = deeznes::console;

namespace deeznes {
namespace app {

pat_table_display::pat_table_display(deeznes::console::nes_console& console)
    : console_(console)
{
}

void pat_table_display::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (uint16_t addr = 0x0000; addr <= 0x0FFF; ++addr)
    {
        uint8_t val = console_.ppu_readu8(addr);
    }
}

} // namespace app
} // namespace deeznes