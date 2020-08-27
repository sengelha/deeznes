#pragma once

#include "ppu_registers.h"

namespace deeznes {
namespace ppu {

struct ppu_state {
  ppu_state() : cycles(0), scanline(0) {}

  ppu_registers regs;
  uint16_t cycles;
  int16_t scanline;
};

} // namespace ppu
} // namespace deeznes
