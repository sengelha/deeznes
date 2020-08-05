#pragma once

#include <cpu/m6502_state.h>
#include <ppu/ppu_state.h>

namespace deeznes
{
namespace console
{

struct nes_console_state
{
	deeznes::cpu::m6502_state cpu_state;
	deeznes::ppu::ppu_state ppu_state;
};

} // namespace console
} // namespace deeznes