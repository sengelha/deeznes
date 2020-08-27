#pragma once

#include "m6502_callbacks.h"
#include "m6502_flags.h"
#include "m6502_state.h"
#include <cstdint>
#include <iostream>
#include <utility>

namespace deeznes {
namespace cpu {

class m6502 {
  m6502_state state_;
  m6502_callbacks *cb_;

  inline void set_carry(bool c) {
    if (c) {
      state_.regs.P |= carry_flag;
    } else {
      state_.regs.P &= ~carry_flag;
    }
  }
  inline void set_overflow(bool c) {
    if (c) {
      state_.regs.P |= overflow_flag;
    } else {
      state_.regs.P &= ~overflow_flag;
    }
  }
  inline void set_zero(bool c) {
    if (c) {
      state_.regs.P |= zero_flag;
    } else {
      state_.regs.P &= ~zero_flag;
    }
  }
  inline void set_sign(bool c) {
    if (c) {
      state_.regs.P |= sign_flag;
    } else {
      state_.regs.P &= ~sign_flag;
    }
  }

  inline int8_t reads8imm() { return (int8_t)readu8imm(); }

  inline uint8_t readu8abs() { return cb_->readu8(readu16imm()); }
  inline std::pair<uint8_t, bool> readu8abx() {
    uint16_t addr = readu16imm();
    uint16_t addr2 = addr + state_.regs.X;
    bool page_crossed = (addr & 0xFF00) != (addr2 & 0xFF00);
    return std::make_pair(cb_->readu8(addr2), page_crossed);
  }
  inline std::pair<uint8_t, bool> readu8aby() {
    uint16_t addr = readu16imm();
    uint16_t addr2 = addr + state_.regs.Y;
    bool page_crossed = (addr & 0xFF00) != (addr2 & 0xFF00);
    return std::make_pair(cb_->readu8(addr2), page_crossed);
  }
  inline uint8_t readu8imm() { return cb_->readu8(state_.regs.PC); }
  inline uint8_t readu8ixx() {
    uint8_t v1 = readu8imm() + state_.regs.X;
    uint16_t addr = readu16pgwrap(v1);
    return cb_->readu8(addr);
  }
  inline std::pair<uint8_t, bool> readu8ixy() {
    uint16_t addr = readu16pgwrap(readu8imm());
    uint16_t addr2 = addr + state_.regs.Y;
    bool page_crossed = (addr & 0xFF00) != (addr2 & 0xFF00);
    return std::make_pair(cb_->readu8(addr2), page_crossed);
  }
  inline uint8_t readu8zpg() { return cb_->readu8(readu8imm()); }
  inline uint8_t readu8zpx() {
    uint8_t zpgaddr = readu8imm() + state_.regs.X;
    return cb_->readu8(zpgaddr);
  }
  inline uint8_t readu8zpy() {
    uint8_t zpgaddr = readu8imm() + state_.regs.Y;
    return cb_->readu8(zpgaddr);
  }

  inline uint16_t readu16imm() { return cb_->readu16(state_.regs.PC); }
  inline uint16_t readu16pgwrap(uint16_t addr) {
    uint8_t v1 = cb_->readu8(addr);
    uint8_t v2 = cb_->readu8((addr & 0xFF) == 0xFF ? addr - 0xFF : addr + 1);
    uint16_t u16 = (v2 << 8) | v1;
    return u16;
  }

  inline void writeu8abs(uint8_t val) { cb_->writeu8(readu16imm(), val); }
  inline void writeu8abx(uint8_t val) {
    cb_->writeu8(readu16imm() + state_.regs.X, val);
  }
  inline void writeu8aby(uint8_t val) {
    cb_->writeu8(readu16imm() + state_.regs.Y, val);
  }
  inline void writeu8ixx(uint8_t val) {
    uint8_t v1 = readu8imm() + state_.regs.X;
    uint16_t addr = readu16pgwrap(v1);
    cb_->writeu8(addr, val);
  }
  inline void writeu8ixy(uint8_t val) {
    cb_->writeu8(readu16pgwrap(readu8imm()) + state_.regs.Y, val);
  }
  inline void writeu8zpg(uint8_t val) { return cb_->writeu8(readu8imm(), val); }
  inline void writeu8zpx(uint8_t val) {
    uint8_t addr = readu8imm() + state_.regs.X;
    return cb_->writeu8(addr, val);
  }
  inline void writeu8zpy(uint8_t val) {
    uint8_t addr = readu8imm() + state_.regs.Y;
    return cb_->writeu8(addr, val);
  }

  inline uint8_t popu8() {
    ++state_.regs.S;
    return cb_->readu8(0x0100 + state_.regs.S);
  }
  inline uint16_t popu16() {
    state_.regs.S += 2;
    return cb_->readu16(0x0100 + state_.regs.S - 1);
  }
  inline void pushu8(uint8_t val) {
    cb_->writeu8(0x0100 + state_.regs.S, val);
    state_.regs.S -= 1;
  }
  inline void pushu16(uint16_t val) {
    cb_->writeu16(0x0100 + state_.regs.S - 1, val);
    state_.regs.S -= 2;
  }

public:
  m6502(m6502_callbacks *cb) : cb_(cb) {}
  m6502(const m6502_state &state, m6502_callbacks *cb)
      : state_(state), cb_(cb) {}
  m6502(m6502_state &&state, m6502_callbacks *cb) noexcept
      : state_(std::move(state)), cb_(cb) {}
  m6502(const m6502 &) = delete;
  m6502 &operator=(const m6502 &) = delete;

  uint_fast32_t run(uint_fast32_t maxcycles);
  m6502_state state() const { return state_; }
  void set_state(const m6502_state &state) { state_ = state; }
  void set_state(m6502_state &&state) { state_ = std::move(state); }
};

} // namespace cpu
} // namespace deeznes
