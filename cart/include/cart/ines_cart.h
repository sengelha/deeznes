#pragma once

#include <cart/nes_cart.h>

namespace deeznes {
namespace cart {

class ines_cart : public nes_cart {
  char prg_rom0_[16384];
  char prg_rom1_[16384];

public:
  ines_cart(const char *filename);
  uint8_t readu8(uint16_t addr) const override final;
  void writeu8(uint16_t addr, uint8_t val) override final;
};

} // namespace cart
} // namespace deeznes
