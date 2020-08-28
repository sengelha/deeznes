#pragma once

#include <cassert>
#include <cpu/m6502.h>

class test_mem : public deeznes::cpu::m6502_callbacks {
  uint8_t *instr_mem_;
  int instr_mem_len_;
  uint8_t *ram_;
  int ram_len_;
  uint8_t fffe;
  uint8_t ffff;

public:
  test_mem(uint8_t *instr_mem, size_t instr_mem_len)
      : instr_mem_(instr_mem), instr_mem_len_(instr_mem_len), ram_(nullptr),
        ram_len_(0) {}
  test_mem(uint8_t *instr_mem, size_t instr_mem_len, uint8_t *ram,
           size_t ram_len)
      : instr_mem_(instr_mem), instr_mem_len_(instr_mem_len), ram_(ram),
        ram_len_(ram_len) {}

  uint8_t readu8(uint16_t addr) const final override {
    if (addr < 0x1000) {
      assert(addr < ram_len_);
      return ram_[addr];
    } else if (addr >= 0xC000 && addr < 0xFFFE) {
      assert(addr - 0xC000 < instr_mem_len_);
      return instr_mem_[addr - 0xC000];
    } else if (addr == 0xFFFE) {
      return fffe;
    } else if (addr == 0xFFFF) {
      return ffff;
    } else {
      assert(false);
      return 0;
    }
  }

  void writeu8(uint16_t addr, uint8_t val) final override {
    if (addr < 0x1000) {
      assert(addr < ram_len_);
      ram_[addr] = val;
    } else if (addr == 0xFFFE) {
      fffe = val;
    } else if (addr == 0xFFFF) {
      ffff = val;
    } else {
      assert(false);
    }
  }
};