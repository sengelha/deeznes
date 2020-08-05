#include <iostream>
#include "m6502_opcode.h"

namespace deeznes {
namespace cpu {

std::ostream&
operator<<(std::ostream& os, const m6502_opcode opcode)
{
    switch (opcode) {
    case m6502_opcode::ADC: os << "ADC"; break;
    case m6502_opcode::AND: os << "AND"; break;
    case m6502_opcode::ASL: os << "ASL"; break;
    case m6502_opcode::BCC: os << "BCC"; break;
    case m6502_opcode::BCS: os << "BCS"; break;
    case m6502_opcode::BEQ: os << "BEQ"; break;
    case m6502_opcode::BIT: os << "BIT"; break;
    case m6502_opcode::BMI: os << "BMI"; break;
    case m6502_opcode::BNE: os << "BNE"; break;
    case m6502_opcode::BPL: os << "BPL"; break;
    case m6502_opcode::BVC: os << "BVC"; break;
    case m6502_opcode::BVS: os << "BVS"; break;
    case m6502_opcode::CLC: os << "CLC"; break;
    case m6502_opcode::CLD: os << "CLD"; break;
    case m6502_opcode::CLV: os << "CLV"; break;
    case m6502_opcode::CMP: os << "CMP"; break;
    case m6502_opcode::CPX: os << "CPX"; break;
    case m6502_opcode::CPY: os << "CPY"; break;
    case m6502_opcode::DCP: os << "DCP"; break;
    case m6502_opcode::DEC: os << "DEC"; break;
    case m6502_opcode::DEX: os << "DEX"; break;
    case m6502_opcode::DEY: os << "DEY"; break;
    case m6502_opcode::EOR: os << "EOR"; break;
    case m6502_opcode::INC: os << "INC"; break;
    case m6502_opcode::INX: os << "INX"; break;
    case m6502_opcode::INY: os << "INY"; break;
    case m6502_opcode::ISB: os << "ISB"; break;
    case m6502_opcode::JMP: os << "JMP"; break;
    case m6502_opcode::JSR: os << "JSR"; break;
    case m6502_opcode::LAX: os << "LAX"; break;
    case m6502_opcode::LDA: os << "LDA"; break;
    case m6502_opcode::LDX: os << "LDX"; break;
    case m6502_opcode::LDY: os << "LDY"; break;
    case m6502_opcode::LSR: os << "LSR"; break;
    case m6502_opcode::NOP: os << "NOP"; break;
    case m6502_opcode::ORA: os << "ORA"; break;
    case m6502_opcode::PHA: os << "PHA"; break;
    case m6502_opcode::PHP: os << "PHP"; break;
    case m6502_opcode::PLA: os << "PLA"; break;
    case m6502_opcode::PLP: os << "PLP"; break;
    case m6502_opcode::RLA: os << "RLA"; break;
    case m6502_opcode::ROL: os << "ROL"; break;
    case m6502_opcode::ROR: os << "ROR"; break;
    case m6502_opcode::RRA: os << "RRA"; break;
    case m6502_opcode::RTI: os << "RTI"; break;
    case m6502_opcode::RTS: os << "RTS"; break;
    case m6502_opcode::SAX: os << "SAX"; break;
    case m6502_opcode::SBC: os << "SBC"; break;
    case m6502_opcode::SEC: os << "SEC"; break;
    case m6502_opcode::SED: os << "SED"; break;
    case m6502_opcode::SEI: os << "SEI"; break;
    case m6502_opcode::SLO: os << "SLO"; break;
    case m6502_opcode::SRE: os << "SRE"; break;
    case m6502_opcode::STA: os << "STA"; break;
    case m6502_opcode::STX: os << "STX"; break;
    case m6502_opcode::STY: os << "STY"; break;
    case m6502_opcode::TAX: os << "TAX"; break;
    case m6502_opcode::TAY: os << "TAY"; break;
    case m6502_opcode::TSX: os << "TSX"; break;
    case m6502_opcode::TXA: os << "TXA"; break;
    case m6502_opcode::TXS: os << "TXS"; break;
    case m6502_opcode::TYA: os << "TYA"; break;
    default: os << "???"; break;
    }
    return os;
}

}
}