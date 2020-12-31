#pragma once

#include <cstdint>

namespace deeznes {
namespace ppu {

class ppu_callbacks {
  public:
    virtual ~ppu_callbacks() = default;
    virtual uint8_t readu8(uint16_t addr) const = 0;
    virtual void vblank_nmi() = 0;
};

} // namespace ppu
} // namespace deeznes
