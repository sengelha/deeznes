#pragma once

#include <cstdint>

namespace deeznes
{
namespace cpu
{

class m6502_callbacks
{
public:
	virtual ~m6502_callbacks() = default;
	virtual uint8_t readu8(uint16_t addr) const = 0;
	virtual void writeu8(uint16_t addr, uint8_t val) = 0;

	inline uint16_t readu16(uint16_t addr) const
	{
		return readu8(addr) | (readu8(addr + 1) << 8);
	}
	inline void writeu16(uint16_t addr, uint16_t val)
	{
		writeu8(addr, val & 0xFF);
		writeu8(addr + 1, val >> 8);
	}
};

} // namespace cpu
} // namespace deeznes