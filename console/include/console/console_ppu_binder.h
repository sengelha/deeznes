#pragma once

#include <cstdint>
#include <ppu/ppu_callbacks.h>

namespace deeznes {
namespace console {

class nes_console;

class console_ppu_binder : public deeznes::ppu::ppu_callbacks {
private:
  nes_console *console_;

public:
  console_ppu_binder(nes_console *c) : console_(c) {}
  uint8_t readu8(uint16_t addr) const override final;
  void vblank_nmi() override final;
};

} // namespace console
} // namespace deeznes