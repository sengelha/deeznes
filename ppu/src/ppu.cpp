#include <assert.h>
#include <ppu/ppu.h>
#include <stdexcept>

namespace deeznes {
namespace ppu {

uint_fast32_t ppu::run(uint_fast32_t maxcycles) {
  for (auto i = 0; i < maxcycles; ++i)
    step();

  return maxcycles;
}

ppu_state ppu::state() const { return state_; }

void ppu::step() {
  if (state_.scanline == -1) {
    // Pre-render scaneline
  } else if (state_.scanline >= 0 && state_.scanline <= 239) {
    // Visible scanlines
  } else if (state_.scanline == 240) {
    // Post-render scanline
    if (state_.cycles == 0) {
      // TODO: draw frame
    }
  } else if (state_.scanline == 241) {
    // Vertical blanking line
    if (state_.cycles == 1) {
      if (!(state_.regs.ppustatus & STATUS_VBLANK_FLAG)) {
        state_.regs.ppustatus |= STATUS_VBLANK_FLAG;
      }
      if (state_.regs.ppuctrl & CTRL1_VBLANK_ENABLE) {
        // TODO: issue vblank nmi
      }
    }
  } else if (state_.scanline <= 260) {
    // Vertical blanking line
  } else {
    assert(false);
  }

  ++state_.cycles;
  if (state_.cycles == 341) {
    state_.cycles = 0;
    ++state_.scanline;
    if (state_.scanline == 261)
      state_.scanline = -1;
  }
}

} // namespace ppu
} // namespace deeznes