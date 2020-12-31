#include "pat_table_display.h"
#include "pat_tile.h"

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

    // $0000-$0FFF is 256 tiles, each one is 16 bytes
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            pat_tile tile(console_, 16*y+x);
            tile.setPosition(x*8, y*8);
            target.draw(tile, states);
        }
    }
    // $1000-$1FFF is 256 tiles, each one is 16 bytes
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            pat_tile tile(console_, 256 + 16*y+x);
            tile.setPosition(8*16 + x*8, y*8);
            target.draw(tile, states);
        }
    }
}

} // namespace app
} // namespace deeznes