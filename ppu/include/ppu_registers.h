#pragma once

namespace deeznes
{
namespace ppu
{

struct ppu_registers
{
	ppu_registers()
		: ppuctrl(0), ppumask(0), ppustatus(0), oamaddr(0)
		, oamdata(0), ppuscroll(0), ppuaddr(0), ppudata(0)
		, oamdma(0) {}

	uint8_t ppuctrl;
	uint8_t ppumask;
	uint8_t ppustatus;
	uint8_t oamaddr;
	uint8_t oamdata;
	uint8_t ppuscroll;
	uint8_t ppuaddr;
	uint8_t ppudata;
	uint8_t oamdma;
};

} // namespace ppu
} // namespace deeznes
