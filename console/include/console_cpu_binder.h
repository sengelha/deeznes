#pragma once

#include <cstdint>
#include <cpu/m6502_callbacks.h>

namespace deeznes
{
namespace console
{

class nes_console;

class console_cpu_binder : public deeznes::cpu::m6502_callbacks
{
private:
	nes_console *console_;

public:
	console_cpu_binder(nes_console *c) : console_(c) {}
	uint8_t readu8(uint16_t addr) const override final;
	void writeu8(uint16_t addr, uint8_t val) override final;
};

} // namespace console
} // namespace deeznes