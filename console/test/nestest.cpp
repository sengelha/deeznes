#include <console/nes_console.h>
#include <cpu/m6502_disassembler.h>
#include <gtest/gtest.h>
#include <array>
#include <fstream>

using namespace deeznes::console;
using namespace deeznes::cpu;
using namespace std;

static ostream &
print_state(ostream &os, nes_console &console)
{
	nes_console_state state = console.state();
	console_cpu_binder binder(&console);
	m6502_disassembler disasm(&binder);
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
			   << hex << uppercase << setw(2) << setfill('0') << (int)binder.readu8(addr)
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
		uint8_t val = binder.readu8(addr2);
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
		uint8_t val = binder.readu8(addr2);
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
		uint16_t val = (binder.readu8(addr + 1) << 8) | binder.readu8(addr);
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
		uint16_t addr = (binder.readu8((addend + 1) & 0xFF) << 8) | binder.readu8(addend);
		uint8_t val = binder.readu8(addr);
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
		uint16_t val1 = (binder.readu8((instr.bytes[1] + 1) & 0xFF) << 8) | binder.readu8(instr.bytes[1]);
		uint16_t val2 = val1 + state.cpu_state.regs.Y;
		uint8_t val3 = binder.readu8(val2);
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
		uint8_t curr_val = binder.readu8(addr);
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
		uint8_t val = binder.readu8(addr);
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
		uint8_t val = binder.readu8(addr);
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
	   << "SL:" << dec << (int)state.ppu_state.scanline;
	return os;
}

TEST(console_rom_tests, nestest)
{
	nes_console console;
	console.insert_cart("roms/nestest.nes");
	console.power_on();

	// nestest.log tests a specific subroutine of nestest that starts at $C000
	// so jump there now.
	nes_console_state state = console.state();
	state.cpu_state.regs.A = 0x00;
	state.cpu_state.regs.X = 0x00;
	state.cpu_state.regs.Y = 0x00;
	state.cpu_state.regs.P = 0x24;
	state.cpu_state.regs.S = 0xFD;
	state.cpu_state.regs.PC = 0xC000;
	state.ppu_state.cycles = 0;
	state.ppu_state.scanline = 241;
	console.set_state(state);

	// nestest.log requires a specific state for certain things
	//binder.writeu8(0x4004, 0xFF);
	//binder.writeu8(0x4005, 0xFF);
	//binder.writeu8(0x4006, 0xFF);
	//binder.writeu8(0x4007, 0xFF);
	//binder.writeu8(0x4015, 0xFF);

	ifstream logf;
	logf.open("roms/nestest.log");
	ASSERT_TRUE(logf.is_open());

	std::string expected;
	while (getline(logf, expected))
	{
		std::stringstream ss;
		print_state(ss, console);
		std::string actual = ss.str();

		ASSERT_EQ(expected, actual);

		console.run(1);
	}
}