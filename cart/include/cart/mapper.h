#pragma once

#include <cstdint>

namespace deeznes {
namespace cart {

class mapper
{
public:
    virtual ~mapper() = default;
    virtual uint8_t cpu_readu8(uint16_t addr) const = 0;
    virtual uint8_t ppu_readu8(uint16_t addr) const = 0;
};

} // namespace cart
} // namespace deeznes
