#pragma once

#include "m6502_addrmode.h"
#include "m6502_opcode.h"
#include <cpu/m6502_callbacks.h>

namespace deeznes {
namespace cpu {

struct m6502_instr {
  int num_bytes;
  uint8_t bytes[3];
  m6502_opcode opcode;
  m6502_addrmode addrmode;
  bool non_standard;
};

class m6502_disassembler {
  const deeznes::cpu::m6502_callbacks *cb_;

public:
  m6502_disassembler(const deeznes::cpu::m6502_callbacks *cb) : cb_(cb) {}

  m6502_instr disasm_at(uint16_t addr);
};

} // namespace cpu
} // namespace deeznes