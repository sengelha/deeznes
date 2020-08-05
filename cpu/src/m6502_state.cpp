#include <iostream>
#include <cpu/m6502_state.h>

using namespace deeznes::cpu;

std::ostream &operator<<(std::ostream &os, const m6502_state &state)
{
	os << "A: " << state.regs.A
	   << " ...TODO";
	return os;
}