#pragma once

#include <iostream>
#include "m6502_registers.h"

namespace deeznes
{
namespace cpu
{

struct m6502_state
{
	m6502_registers regs;
	uint32_t cycles;
};

std::ostream &operator<<(std::ostream &os, const m6502_state &state);

} // namespace cpu
} // namespace deeznes