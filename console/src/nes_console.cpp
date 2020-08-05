#include <algorithm>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <string.h>
#include <cpu/m6502_disassembler.h>
#include <console/nes_console.h>

using namespace std;
using namespace deeznes::cart;
using namespace deeznes::cpu;
using namespace deeznes::io;
using namespace deeznes::ppu;

namespace deeznes
{
namespace console
{

std::ostream &operator<<(std::ostream &os, const nes_console &console)
{
	nes_console_state state = console.state();
	m6502_disassembler disasm(&console.cpu_binder_);
	m6502_instr instr = disasm.disasm_at(state.cpu_state.regs.PC);

	os << hex << uppercase << setw(4) << setfill('0') << (int)state.cpu_state.regs.PC
	   << "  ";

	for (int i = 0; i < instr.num_bytes; ++i)
	{
		os << hex << uppercase << setw(2) << setfill('0') << (int)instr.bytes[i]
		   << " ";
	}
	os << std::string(9 - 3 * instr.num_bytes, ' ')
	   << (instr.non_standard ? '*' : ' ')
	   << instr.opcode
	   << " ";

	switch (instr.addrmode)
	{
	case m6502_addrmode::ABS:
	{
		uint16_t addr = (instr.bytes[2] << 8) | instr.bytes[1];
		os << "$"
		   << hex << uppercase << setw(4) << setfill('0') << (int)addr
		   << " ";

		static constexpr m6502_opcode no_curr_val_opcodes[] = {
			m6502_opcode::JMP, m6502_opcode::JSR};
		if (find(begin(no_curr_val_opcodes), end(no_curr_val_opcodes), instr.opcode) == end(no_curr_val_opcodes))
		{
			os << "= "
			   << hex << uppercase << setw(2) << setfill('0') << (int)console.cpu_binder_.readu8(addr)
			   << "                 ";
		}
		else
		{
			os << "                     ";
		}
		break;
	}
	case m6502_addrmode::ABX:
	{
		uint16_t addr = (instr.bytes[2] << 8) | instr.bytes[1];
		uint16_t addr2 = addr + state.cpu_state.regs.X;
		uint8_t val = console.cpu_binder_.readu8(addr2);
		os << "$"
		   << hex << uppercase << setw(4) << setfill('0') << (int)addr
		   << ",X @ "
		   << hex << uppercase << setw(4) << setfill('0') << (int)addr2
		   << " = "
		   << hex << uppercase << setw(2) << setfill('0') << (int)val
		   << "        ";
		break;
	}
	case m6502_addrmode::ABY:
	{
		uint16_t addr = (instr.bytes[2] << 8) | instr.bytes[1];
		uint16_t addr2 = addr + state.cpu_state.regs.Y;
		uint8_t val = console.cpu_binder_.readu8(addr2);
		os << "$"
		   << hex << uppercase << setw(4) << setfill('0') << (int)addr
		   << ",Y @ "
		   << hex << uppercase << setw(4) << setfill('0') << (int)addr2
		   << " = "
		   << hex << uppercase << setw(2) << setfill('0') << (int)val
		   << "        ";
		break;
	}
	case m6502_addrmode::ACC:
		os << "A                          ";
		break;
	case m6502_addrmode::IMM:
		os << "#$"
		   << hex << uppercase << setw(2) << setfill('0') << (int)instr.bytes[1]
		   << "                       ";
		break;
	case m6502_addrmode::IMP:
		os << "                           ";
		break;
	case m6502_addrmode::IND:
	{
		uint16_t addr = (instr.bytes[2] << 8) | instr.bytes[1];
		uint16_t val = (console.cpu_binder_.readu8(addr + 1) << 8) | console.cpu_binder_.readu8(addr);
		os << "($"
		   << hex << uppercase << setw(4) << setfill('0') << addr
		   << ") = "
		   << hex << uppercase << setw(4) << setfill('0') << val
		   << "             ";
		break;
	}
	case m6502_addrmode::IXX:
	{
		uint8_t addend = instr.bytes[1] + state.cpu_state.regs.X;
		uint16_t addr = (console.cpu_binder_.readu8((addend + 1) & 0xFF) << 8) | console.cpu_binder_.readu8(addend);
		uint8_t val = console.cpu_binder_.readu8(addr);
		os << "($"
		   << (int)instr.bytes[1]
		   << ",X) @ "
		   << (int)addend
		   << " = "
		   << hex << uppercase << setw(4) << setfill('0') << addr
		   << " = "
		   << hex << uppercase << setw(2) << setfill('0') << (int)val
		   << "   ";
		break;
	}
	case m6502_addrmode::IXY:
	{
		uint16_t val1 = (console.cpu_binder_.readu8((instr.bytes[1] + 1) & 0xFF) << 8) | console.cpu_binder_.readu8(instr.bytes[1]);
		uint16_t val2 = val1 + state.cpu_state.regs.Y;
		uint8_t val3 = console.cpu_binder_.readu8(val2);
		os << "($"
		   << (int)instr.bytes[1]
		   << "),Y = "
		   << hex << uppercase << setw(4) << setfill('0') << (int)val1
		   << " @ "
		   << hex << uppercase << setw(4) << setfill('0') << (int)val2
		   << " = "
		   << hex << uppercase << setw(2) << setfill('0') << (int)val3
		   << " ";
		break;
	}
	case m6502_addrmode::REL:
	{
		uint16_t addr = state.cpu_state.regs.PC + 2 + (int8_t)instr.bytes[1];
		os << "$"
		   << hex << uppercase << setw(4) << setfill('0') << (int)addr
		   << "                      ";
		break;
	}
	case m6502_addrmode::ZPG:
	{
		uint16_t addr = instr.bytes[1];
		uint8_t curr_val = console.cpu_binder_.readu8(addr);
		os << "$"
		   << hex << uppercase << setw(2) << setfill('0') << (int)instr.bytes[1]
		   << " = "
		   << hex << uppercase << setw(2) << setfill('0') << (int)curr_val
		   << "                   ";
		break;
	}
	case m6502_addrmode::ZPX:
	{
		uint8_t addr = instr.bytes[1] + state.cpu_state.regs.X;
		uint8_t val = console.cpu_binder_.readu8(addr);
		os << "$"
		   << hex << uppercase << setw(2) << setfill('0') << (int)instr.bytes[1]
		   << ",X @ "
		   << hex << uppercase << setw(2) << setfill('0') << (int)addr
		   << " = "
		   << hex << uppercase << setw(2) << setfill('0') << (int)val
		   << "            ";
		break;
	}
	case m6502_addrmode::ZPY:
	{
		uint8_t addr = instr.bytes[1] + state.cpu_state.regs.Y;
		uint8_t val = console.cpu_binder_.readu8(addr);
		os << "$"
		   << hex << uppercase << setw(2) << setfill('0') << (int)instr.bytes[1]
		   << ",Y @ "
		   << hex << uppercase << setw(2) << setfill('0') << (int)addr
		   << " = "
		   << hex << uppercase << setw(2) << setfill('0') << (int)val
		   << "            ";
		break;
	}
	}

	os << " "
	   << "A:" << hex << uppercase << setw(2) << setfill('0') << (int)state.cpu_state.regs.A
	   << " "
	   << "X:" << hex << uppercase << setw(2) << setfill('0') << (int)state.cpu_state.regs.X
	   << " "
	   << "Y:" << hex << uppercase << setw(2) << setfill('0') << (int)state.cpu_state.regs.Y
	   << " "
	   << "P:" << hex << uppercase << setw(2) << setfill('0') << (int)state.cpu_state.regs.P
	   << " "
	   << "SP:" << hex << uppercase << setw(2) << setfill('0') << (int)state.cpu_state.regs.S
	   << " "
	   << "CYC:" << dec << setw(3) << setfill(' ') << (int)state.ppu_state.cycles
	   << " "
	   << "SL:" << dec << (int)state.ppu_state.scanline
	   << " "
	   << "C:" << hex << uppercase << setw(2) << setfill('0') << (int)state.ppu_state.regs.ppuctrl
	   << " "
	   << "M:" << hex << uppercase << setw(2) << setfill('0') << (int)state.ppu_state.regs.ppumask
	   << " "
	   << "S:" << hex << uppercase << setw(2) << setfill('0') << (int)state.ppu_state.regs.ppustatus;
	return os;
}

void nes_console::insert_cart(const char *filename)
{
	cart_ = nes_cart(filename);
}

void nes_console::power_on()
{
	assert(!power_on_);
	// CPUs boot effectively by a JMP ($FFFC)
	// TODO: Verify power-on state from document, create unit test
	m6502_state state;
	state.regs.A = 0;
	state.regs.X = 0;
	state.regs.Y = 0;
	state.regs.P = 0;
	state.regs.S = 0;
	state.regs.PC = cpu_binder_.readu16(0xFFFC);
	state.cycles = 0;
	cpu_.set_state(state);
	memset(ram_, 0, sizeof(ram_));
	memset(sound_regs_, 0xFF, sizeof(sound_regs_));
	sound_switch_ = 0xFF;
	power_on_ = true;
}

uint_fast32_t
nes_console::run(uint_fast32_t maxcycles)
{
	auto cpu_cycles = cpu_.run(maxcycles);
	ppu_.run(cpu_cycles * 3);
	return cpu_cycles;
}

void nes_console::set_state(const nes_console_state &state)
{
	cpu_.set_state(state.cpu_state);
	ppu_.set_state(state.ppu_state);
}

nes_console_state
nes_console::state() const
{
	nes_console_state state;
	state.cpu_state = cpu_.state();
	state.ppu_state = ppu_.state();
	return state;
}

} // namespace console
} // namespace deeznes
