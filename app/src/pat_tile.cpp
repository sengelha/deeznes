#include "pat_tile.h"
#include <boost/format.hpp>

namespace console = deeznes::console;

namespace deeznes {
namespace app {

pat_tile::pat_tile(deeznes::console::nes_console& console, int indx)
    : console_(console), indx_(indx)
{
}

void pat_tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::Uint8 pixels[8*8*4];

    sf::Uint8* p = pixels;
    for (int i = 0; i < 8; ++i) {
        uint16_t addr = 16 * indx_ + i;
        uint8_t val = console_.ppu_readu8(addr) | console_.ppu_readu8(addr + 8);
        for (int j = 7; j >= 0; --j) {
            bool set = (val >> j) & 0x01;
            *p++ = (set ? 0xFF : 0x00);
            *p++ = (set ? 0xFF : 0x00);
            *p++ = (set ? 0xFF : 0x00);
            *p++ = (set ? 0xFF : 0x00);
        }
    }

    sf::Image image;
    image.create(8, 8, pixels);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    target.draw(sprite, states);
}

} // namespace app
} // namespace deeznes