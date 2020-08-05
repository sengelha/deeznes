#pragma once

#include <fstream>

namespace deeznes
{
namespace cart
{

class nes_cart
{
    char prg_rom0_[16384];
    char prg_rom1_[16384];

public:
    nes_cart(const char *filename);
    uint8_t readu8(uint16_t addr) const;
};

} // namespace cart
} // namespace deeznes
