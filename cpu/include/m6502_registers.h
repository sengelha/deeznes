#pragma once

namespace deeznes
{
namespace cpu
{

struct m6502_registers
{
	uint8_t A;
	uint8_t P;
	uint8_t X;
	uint8_t Y;
	uint8_t S;
	uint16_t PC;
};

} // namespace cpu
} // namespace deeznes