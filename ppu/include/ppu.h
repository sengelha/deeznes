#pragma once

#include "ppu_callbacks.h"
#include "ppu_flags.h"
#include "ppu_state.h"
#include <cstdint>
#include <utility>

namespace deeznes {
namespace ppu {

class ppu {
private:
  ppu_callbacks *cb_;
  ppu_state state_;

  void step();

public:
  ppu(ppu_callbacks *cb) : cb_(cb) {}

  // Run for up to maxcycles PPU cycles (typically 3 * CPU cycles)
  uint_fast32_t run(uint_fast32_t maxcycles);

  // Individual PPU registers
  uint8_t ctrl() const { return state_.regs.ppuctrl; }
  void set_ctrl(uint8_t val) { state_.regs.ppuctrl = val; }
  uint8_t mask() const { return state_.regs.ppumask; }
  void set_mask(uint8_t val) { state_.regs.ppumask = val; }
  uint8_t scroll() const { return state_.regs.ppuscroll; }
  void set_scroll(uint8_t val) { state_.regs.ppuscroll = val; }
  uint8_t status() const { return state_.regs.ppustatus; }
  uint8_t ppuaddr() const { return state_.regs.ppuaddr; }
  void set_ppuaddr(uint8_t val) { state_.regs.ppuaddr = val; }
  uint8_t ppudata() const { return state_.regs.ppudata; }
  void set_ppudata(uint8_t val) { state_.regs.ppudata = val; }

  // Batch state management
  ppu_state state() const;
  void set_state(const ppu_state &state) { state_ = state; }
  void set_state(ppu_state &&state) { state_ = std::move(state); }
};

} // namespace ppu
} // namespace deeznes