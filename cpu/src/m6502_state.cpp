#include <cpu/m6502_state.h>
#include <iomanip>
#include <iostream>

namespace deeznes {
namespace cpu {

std::ostream &operator<<(std::ostream &os, const m6502_state &state) {
    os << "A:" << std::hex << std::uppercase << std::setw(2)
       << std::setfill('0') << (int)state.regs.A;
    os << " X:" << std::hex << std::uppercase << std::setw(2)
       << std::setfill('0') << (int)state.regs.X;
    os << " Y:" << std::hex << std::uppercase << std::setw(2)
       << std::setfill('0') << (int)state.regs.Y;
    os << " P:" << std::hex << std::uppercase << std::setw(2)
       << std::setfill('0') << (int)state.regs.P;
    os << " S:" << std::hex << std::uppercase << std::setw(2)
       << std::setfill('0') << (int)state.regs.S;
    os << " PC:" << std::hex << std::uppercase << std::setw(4)
       << std::setfill('0') << (int)state.regs.PC;
    os << " CYC:" << std::dec << (int)state.cycles;
    return os;
}

} // namespace cpu
} // namespace deeznes
