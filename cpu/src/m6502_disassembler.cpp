#include <cpu/m6502_disassembler.h>

namespace deeznes {
namespace cpu {

struct instr_info {
  m6502_opcode opcode;
  m6502_addrmode addrmode;
  bool non_standard;
};

static constexpr instr_info INSTR_INFO[] = {
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $00
    {m6502_opcode::ORA, m6502_addrmode::IXX},       // $01
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $02
    {m6502_opcode::SLO, m6502_addrmode::IXX, true}, // $03
    {m6502_opcode::NOP, m6502_addrmode::ZPG, true}, // $04
    {m6502_opcode::ORA, m6502_addrmode::ZPG},       // $05
    {m6502_opcode::ASL, m6502_addrmode::ZPG},       // $06
    {m6502_opcode::SLO, m6502_addrmode::ZPG, true}, // $07
    {m6502_opcode::PHP, m6502_addrmode::IMP},       // $08
    {m6502_opcode::ORA, m6502_addrmode::IMM},       // $09
    {m6502_opcode::ASL, m6502_addrmode::ACC},       // $0A
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $0B
    {m6502_opcode::NOP, m6502_addrmode::ABS, true}, // $0C
    {m6502_opcode::ORA, m6502_addrmode::ABS},       // $0D
    {m6502_opcode::ASL, m6502_addrmode::ABS},       // $0E
    {m6502_opcode::SLO, m6502_addrmode::ABS, true}, // $0F
    {m6502_opcode::BPL, m6502_addrmode::REL},       // $10
    {m6502_opcode::ORA, m6502_addrmode::IXY},       // $11
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $12
    {m6502_opcode::SLO, m6502_addrmode::IXY, true}, // $13
    {m6502_opcode::NOP, m6502_addrmode::ZPX, true}, // $14
    {m6502_opcode::ORA, m6502_addrmode::ZPX},       // $15
    {m6502_opcode::ASL, m6502_addrmode::ZPX},       // $16
    {m6502_opcode::SLO, m6502_addrmode::ZPX, true}, // $17
    {m6502_opcode::CLC, m6502_addrmode::IMP},       // $18
    {m6502_opcode::ORA, m6502_addrmode::ABY},       // $19
    {m6502_opcode::NOP, m6502_addrmode::IMP, true}, // $1A
    {m6502_opcode::SLO, m6502_addrmode::ABY, true}, // $1B
    {m6502_opcode::NOP, m6502_addrmode::ABX, true}, // $1C
    {m6502_opcode::ORA, m6502_addrmode::ABX},       // $1D
    {m6502_opcode::ASL, m6502_addrmode::ABX},       // $1E
    {m6502_opcode::SLO, m6502_addrmode::ABX, true}, // $1F
    {m6502_opcode::JSR, m6502_addrmode::ABS},       // $20
    {m6502_opcode::AND, m6502_addrmode::IXX},       // $21
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $22
    {m6502_opcode::RLA, m6502_addrmode::IXX, true}, // $23
    {m6502_opcode::BIT, m6502_addrmode::ZPG},       // $24
    {m6502_opcode::AND, m6502_addrmode::ZPG},       // $25
    {m6502_opcode::ROL, m6502_addrmode::ZPG},       // $26
    {m6502_opcode::RLA, m6502_addrmode::ZPG, true}, // $27
    {m6502_opcode::PLP, m6502_addrmode::IMP},       // $28
    {m6502_opcode::AND, m6502_addrmode::IMM},       // $29
    {m6502_opcode::ROL, m6502_addrmode::ACC},       // $2A
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $2B
    {m6502_opcode::BIT, m6502_addrmode::ABS},       // $2C
    {m6502_opcode::AND, m6502_addrmode::ABS},       // $2D
    {m6502_opcode::ROL, m6502_addrmode::ABS},       // $2E
    {m6502_opcode::RLA, m6502_addrmode::ABS, true}, // $2F
    {m6502_opcode::BMI, m6502_addrmode::REL},       // $30
    {m6502_opcode::AND, m6502_addrmode::IXY},       // $31
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $32
    {m6502_opcode::RLA, m6502_addrmode::IXY, true}, // $33
    {m6502_opcode::NOP, m6502_addrmode::ZPX, true}, // $34
    {m6502_opcode::AND, m6502_addrmode::ZPX},       // $35
    {m6502_opcode::ROL, m6502_addrmode::ZPX},       // $36
    {m6502_opcode::RLA, m6502_addrmode::ZPX, true}, // $37
    {m6502_opcode::SEC, m6502_addrmode::IMP},       // $38
    {m6502_opcode::AND, m6502_addrmode::ABY},       // $39
    {m6502_opcode::NOP, m6502_addrmode::IMP, true}, // $3A
    {m6502_opcode::RLA, m6502_addrmode::ABY, true}, // $3B
    {m6502_opcode::NOP, m6502_addrmode::ABX, true}, // $3C
    {m6502_opcode::AND, m6502_addrmode::ABX},       // $3D
    {m6502_opcode::ROL, m6502_addrmode::ABX},       // $3E
    {m6502_opcode::RLA, m6502_addrmode::ABX, true}, // $3F
    {m6502_opcode::RTI, m6502_addrmode::IMP},       // $40
    {m6502_opcode::EOR, m6502_addrmode::IXX},       // $41
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $42
    {m6502_opcode::SRE, m6502_addrmode::IXX, true}, // $43
    {m6502_opcode::NOP, m6502_addrmode::ZPG, true}, // $44
    {m6502_opcode::EOR, m6502_addrmode::ZPG},       // $45
    {m6502_opcode::LSR, m6502_addrmode::ZPG},       // $46
    {m6502_opcode::SRE, m6502_addrmode::ZPG, true}, // $47
    {m6502_opcode::PHA, m6502_addrmode::IMP},       // $48
    {m6502_opcode::EOR, m6502_addrmode::IMM},       // $49
    {m6502_opcode::LSR, m6502_addrmode::ACC},       // $4A
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $4B
    {m6502_opcode::JMP, m6502_addrmode::ABS},       // $4C
    {m6502_opcode::EOR, m6502_addrmode::ABS},       // $4D
    {m6502_opcode::LSR, m6502_addrmode::ABS},       // $4E
    {m6502_opcode::SRE, m6502_addrmode::ABS, true}, // $4F
    {m6502_opcode::BVC, m6502_addrmode::REL},       // $50
    {m6502_opcode::EOR, m6502_addrmode::IXY},       // $51
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $52
    {m6502_opcode::SRE, m6502_addrmode::IXY, true}, // $53
    {m6502_opcode::NOP, m6502_addrmode::ZPX, true}, // $54
    {m6502_opcode::EOR, m6502_addrmode::ZPX},       // $55
    {m6502_opcode::LSR, m6502_addrmode::ZPX},       // $56
    {m6502_opcode::SRE, m6502_addrmode::ZPX, true}, // $57
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $58
    {m6502_opcode::EOR, m6502_addrmode::ABY},       // $59
    {m6502_opcode::NOP, m6502_addrmode::IMP, true}, // $5A
    {m6502_opcode::SRE, m6502_addrmode::ABY, true}, // $5B
    {m6502_opcode::NOP, m6502_addrmode::ABX, true}, // $5C
    {m6502_opcode::EOR, m6502_addrmode::ABX},       // $5D
    {m6502_opcode::LSR, m6502_addrmode::ABX},       // $5E
    {m6502_opcode::SRE, m6502_addrmode::ABX, true}, // $5F
    {m6502_opcode::RTS, m6502_addrmode::IMP},       // $60
    {m6502_opcode::ADC, m6502_addrmode::IXX},       // $61
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $62
    {m6502_opcode::RRA, m6502_addrmode::IXX, true}, // $63
    {m6502_opcode::NOP, m6502_addrmode::ZPG, true}, // $64
    {m6502_opcode::ADC, m6502_addrmode::ZPG},       // $65
    {m6502_opcode::ROR, m6502_addrmode::ZPG},       // $66
    {m6502_opcode::RRA, m6502_addrmode::ZPG, true}, // $67
    {m6502_opcode::PLA, m6502_addrmode::IMP},       // $68
    {m6502_opcode::ADC, m6502_addrmode::IMM},       // $69
    {m6502_opcode::ROR, m6502_addrmode::ACC},       // $6A
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $6B
    {m6502_opcode::JMP, m6502_addrmode::IND},       // $6C
    {m6502_opcode::ADC, m6502_addrmode::ABS},       // $6D
    {m6502_opcode::ROR, m6502_addrmode::ABS},       // $6E
    {m6502_opcode::RRA, m6502_addrmode::ABS, true}, // $6F
    {m6502_opcode::BVS, m6502_addrmode::REL},       // $70
    {m6502_opcode::ADC, m6502_addrmode::IXY},       // $71
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $72
    {m6502_opcode::RRA, m6502_addrmode::IXY, true}, // $73
    {m6502_opcode::NOP, m6502_addrmode::ZPX, true}, // $74
    {m6502_opcode::ADC, m6502_addrmode::ZPX},       // $75
    {m6502_opcode::ROR, m6502_addrmode::ZPX},       // $76
    {m6502_opcode::RRA, m6502_addrmode::ZPX, true}, // $77
    {m6502_opcode::SEI, m6502_addrmode::IMP},       // $78
    {m6502_opcode::ADC, m6502_addrmode::ABY},       // $79
    {m6502_opcode::NOP, m6502_addrmode::IMP, true}, // $7A
    {m6502_opcode::RRA, m6502_addrmode::ABY, true}, // $7B
    {m6502_opcode::NOP, m6502_addrmode::ABX, true}, // $7C
    {m6502_opcode::ADC, m6502_addrmode::ABX},       // $7D
    {m6502_opcode::ROR, m6502_addrmode::ABX},       // $7E
    {m6502_opcode::RRA, m6502_addrmode::ABX, true}, // $7F
    {m6502_opcode::NOP, m6502_addrmode::IMM, true}, // $80
    {m6502_opcode::STA, m6502_addrmode::IXX},       // $81
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $82
    {m6502_opcode::SAX, m6502_addrmode::IXX, true}, // $83
    {m6502_opcode::STY, m6502_addrmode::ZPG},       // $84
    {m6502_opcode::STA, m6502_addrmode::ZPG},       // $85
    {m6502_opcode::STX, m6502_addrmode::ZPG},       // $86
    {m6502_opcode::SAX, m6502_addrmode::ZPG, true}, // $87
    {m6502_opcode::DEY, m6502_addrmode::IMP},       // $88
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $89
    {m6502_opcode::TXA, m6502_addrmode::IMP},       // $8A
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $8B
    {m6502_opcode::STY, m6502_addrmode::ABS},       // $8C
    {m6502_opcode::STA, m6502_addrmode::ABS},       // $8D
    {m6502_opcode::STX, m6502_addrmode::ABS},       // $8E
    {m6502_opcode::SAX, m6502_addrmode::ABS, true}, // $8F
    {m6502_opcode::BCC, m6502_addrmode::REL},       // $90
    {m6502_opcode::STA, m6502_addrmode::IXY},       // $91
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $92
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $93
    {m6502_opcode::STY, m6502_addrmode::ZPX},       // $94
    {m6502_opcode::STA, m6502_addrmode::ZPX},       // $95
    {m6502_opcode::STX, m6502_addrmode::ZPY},       // $96
    {m6502_opcode::SAX, m6502_addrmode::ZPY, true}, // $97
    {m6502_opcode::TYA, m6502_addrmode::IMP},       // $98
    {m6502_opcode::STA, m6502_addrmode::ABY},       // $99
    {m6502_opcode::TXS, m6502_addrmode::IMP},       // $9A
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $9B
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $9C
    {m6502_opcode::STA, m6502_addrmode::ABX},       // $9D
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $9E
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $9F
    {m6502_opcode::LDY, m6502_addrmode::IMM},       // $A0
    {m6502_opcode::LDA, m6502_addrmode::IXX},       // $A1
    {m6502_opcode::LDX, m6502_addrmode::IMM},       // $A2
    {m6502_opcode::LAX, m6502_addrmode::IXX, true}, // $A3
    {m6502_opcode::LDY, m6502_addrmode::ZPG},       // $A4
    {m6502_opcode::LDA, m6502_addrmode::ZPG},       // $A5
    {m6502_opcode::LDX, m6502_addrmode::ZPG},       // $A6
    {m6502_opcode::LAX, m6502_addrmode::ZPG, true}, // $A7
    {m6502_opcode::TAY, m6502_addrmode::IMP},       // $A8
    {m6502_opcode::LDA, m6502_addrmode::IMM},       // $A9
    {m6502_opcode::TAX, m6502_addrmode::IMP},       // $AA
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $AB
    {m6502_opcode::LDY, m6502_addrmode::ABS},       // $AC
    {m6502_opcode::LDA, m6502_addrmode::ABS},       // $AD
    {m6502_opcode::LDX, m6502_addrmode::ABS},       // $AE
    {m6502_opcode::LAX, m6502_addrmode::ABS, true}, // $AF
    {m6502_opcode::BCS, m6502_addrmode::REL},       // $B0
    {m6502_opcode::LDA, m6502_addrmode::IXY},       // $B1
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $B2
    {m6502_opcode::LAX, m6502_addrmode::IXY, true}, // $B3
    {m6502_opcode::LDY, m6502_addrmode::ZPX},       // $B4
    {m6502_opcode::LDA, m6502_addrmode::ZPX},       // $B5
    {m6502_opcode::LDX, m6502_addrmode::ZPY},       // $B6
    {m6502_opcode::LAX, m6502_addrmode::ZPY, true}, // $B7
    {m6502_opcode::CLV, m6502_addrmode::IMP},       // $B8
    {m6502_opcode::LDA, m6502_addrmode::ABY},       // $B9
    {m6502_opcode::TSX, m6502_addrmode::IMP},       // $BA
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $BB
    {m6502_opcode::LDY, m6502_addrmode::ABX},       // $BC
    {m6502_opcode::LDA, m6502_addrmode::ABX},       // $BD
    {m6502_opcode::LDX, m6502_addrmode::ABY},       // $BE
    {m6502_opcode::LAX, m6502_addrmode::ABY, true}, // $BF
    {m6502_opcode::CPY, m6502_addrmode::IMM},       // $C0
    {m6502_opcode::CMP, m6502_addrmode::IXX},       // $C1
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $C2
    {m6502_opcode::DCP, m6502_addrmode::IXX, true}, // $C3
    {m6502_opcode::CPY, m6502_addrmode::ZPG},       // $C4
    {m6502_opcode::CMP, m6502_addrmode::ZPG},       // $C5
    {m6502_opcode::DEC, m6502_addrmode::ZPG},       // $C6
    {m6502_opcode::DCP, m6502_addrmode::ZPG, true}, // $C7
    {m6502_opcode::INY, m6502_addrmode::IMP},       // $C8
    {m6502_opcode::CMP, m6502_addrmode::IMM},       // $C9
    {m6502_opcode::DEX, m6502_addrmode::IMP},       // $CA
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $CB
    {m6502_opcode::CPY, m6502_addrmode::ABS},       // $CC
    {m6502_opcode::CMP, m6502_addrmode::ABS},       // $CD
    {m6502_opcode::DEC, m6502_addrmode::ABS},       // $CE
    {m6502_opcode::DCP, m6502_addrmode::ABS, true}, // $CF
    {m6502_opcode::BNE, m6502_addrmode::REL},       // $D0
    {m6502_opcode::CMP, m6502_addrmode::IXY},       // $D1
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $D2
    {m6502_opcode::DCP, m6502_addrmode::IXY, true}, // $D3
    {m6502_opcode::NOP, m6502_addrmode::ZPX, true}, // $D4
    {m6502_opcode::CMP, m6502_addrmode::ZPX},       // $D5
    {m6502_opcode::DEC, m6502_addrmode::ZPX},       // $D6
    {m6502_opcode::DCP, m6502_addrmode::ZPX, true}, // $D7
    {m6502_opcode::CLD, m6502_addrmode::IMP},       // $D8
    {m6502_opcode::CMP, m6502_addrmode::ABY},       // $D9
    {m6502_opcode::NOP, m6502_addrmode::IMP, true}, // $DA
    {m6502_opcode::DCP, m6502_addrmode::ABY, true}, // $DB
    {m6502_opcode::NOP, m6502_addrmode::ABX, true}, // $DC
    {m6502_opcode::CMP, m6502_addrmode::ABX},       // $DD
    {m6502_opcode::DEC, m6502_addrmode::ABX},       // $DE
    {m6502_opcode::DCP, m6502_addrmode::ABX, true}, // $DF
    {m6502_opcode::CPX, m6502_addrmode::IMM},       // $E0
    {m6502_opcode::SBC, m6502_addrmode::IXX},       // $E1
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $E2
    {m6502_opcode::ISB, m6502_addrmode::IXX, true}, // $E3
    {m6502_opcode::CPX, m6502_addrmode::ZPG},       // $E4
    {m6502_opcode::SBC, m6502_addrmode::ZPG},       // $E5
    {m6502_opcode::INC, m6502_addrmode::ZPG},       // $E6
    {m6502_opcode::ISB, m6502_addrmode::ZPG, true}, // $E7
    {m6502_opcode::INX, m6502_addrmode::IMP},       // $E8
    {m6502_opcode::SBC, m6502_addrmode::IMM},       // $E9
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $EA
    {m6502_opcode::SBC, m6502_addrmode::IMM, true}, // $EB
    {m6502_opcode::CPX, m6502_addrmode::ABS},       // $EC
    {m6502_opcode::SBC, m6502_addrmode::ABS},       // $ED
    {m6502_opcode::INC, m6502_addrmode::ABS},       // $EE
    {m6502_opcode::ISB, m6502_addrmode::ABS, true}, // $EF
    {m6502_opcode::BEQ, m6502_addrmode::REL},       // $F0
    {m6502_opcode::SBC, m6502_addrmode::IXY},       // $F1
    {m6502_opcode::NOP, m6502_addrmode::IMP},       // $F2
    {m6502_opcode::ISB, m6502_addrmode::IXY, true}, // $F3
    {m6502_opcode::NOP, m6502_addrmode::ZPX, true}, // $F4
    {m6502_opcode::SBC, m6502_addrmode::ZPX},       // $F5
    {m6502_opcode::INC, m6502_addrmode::ZPX},       // $F6
    {m6502_opcode::ISB, m6502_addrmode::ZPX, true}, // $F7
    {m6502_opcode::SED, m6502_addrmode::IMP},       // $F8
    {m6502_opcode::SBC, m6502_addrmode::ABY},       // $F9
    {m6502_opcode::NOP, m6502_addrmode::IMP, true}, // $FA
    {m6502_opcode::ISB, m6502_addrmode::ABY, true}, // $FB
    {m6502_opcode::NOP, m6502_addrmode::ABX, true}, // $FC
    {m6502_opcode::SBC, m6502_addrmode::ABX},       // $FD
    {m6502_opcode::INC, m6502_addrmode::ABX},       // $FE
    {m6502_opcode::ISB, m6502_addrmode::ABX, true}, // $FF
};

static int num_bytes(m6502_addrmode addrmode) {
  switch (addrmode) {
  case m6502_addrmode::ABS:
    return 3;
  case m6502_addrmode::ABX:
    return 3;
  case m6502_addrmode::ABY:
    return 3;
  case m6502_addrmode::ACC:
    return 1;
  case m6502_addrmode::IMM:
    return 2;
  case m6502_addrmode::IMP:
    return 1;
  case m6502_addrmode::IND:
    return 3;
  case m6502_addrmode::IXX:
    return 2;
  case m6502_addrmode::IXY:
    return 2;
  case m6502_addrmode::REL:
    return 2;
  case m6502_addrmode::ZPG:
    return 2;
  case m6502_addrmode::ZPX:
    return 2;
  case m6502_addrmode::ZPY:
    return 2;
  }
}

m6502_instr m6502_disassembler::disasm_at(uint16_t addr) {
  const instr_info &ii = INSTR_INFO[cb_->readu8(addr)];

  m6502_instr instr;
  instr.num_bytes = num_bytes(ii.addrmode);
  for (int i = 0; i < instr.num_bytes; ++i) {
    instr.bytes[i] = cb_->readu8(addr + i);
  }
  instr.opcode = ii.opcode;
  instr.addrmode = ii.addrmode;
  instr.non_standard = ii.non_standard;
  return instr;
}

} // namespace cpu
} // namespace deeznes