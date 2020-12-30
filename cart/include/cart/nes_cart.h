#pragma once

#include <cstdint>

namespace deeznes {
namespace cart {

class nes_cart {
public:
  virtual ~nes_cart() = default;
  virtual uint8_t cpu_readu8(uint16_t offset) const = 0;
  virtual uint8_t ppu_readu8(uint16_t offset) const = 0;
};

} // namespace cart
} // namespace deeznes
