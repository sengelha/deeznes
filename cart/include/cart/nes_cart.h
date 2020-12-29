#pragma once

namespace deeznes {
namespace cart {

class nes_cart {
public:
  virtual ~nes_cart() = default;
  virtual uint8_t readu8(uint16_t addr) const = 0;
  virtual void writeu8(uint16_t addr, uint8_t val) = 0;
};

} // namespace cart
} // namespace deeznes
