#include <string.h> // For memcmp
#include <cassert>
#include <iostream>
#include <cart/nes_cart.h>

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

using namespace std;

namespace deeznes
{
namespace cart
{

/*
An iNES file consists of the following sections, in order: 
1. Header (16 bytes)
2. Trainer, if present (0 or 512 bytes)
3. PRG ROM data (16384 * x bytes)
4. CHR ROM data, if present (8192 * y bytes)
5. PlayChoice INST-ROM, if present (0 or 8192 bytes)
6. PlayChoice PROM, if present (16 bytes Data, 16 bytes CounterOut) (this is often missing, see PC10 ROM-Images for details)
7. Occassionally, a 128-byte (or sometimes 127-byte) title at the end of the file. 

The format of the header is as follows:
0-3: Constant $4E $45 $53 $1A ("NES" followed by MS-DOS end-of-file)
4: Size of PRG ROM in 16 KB units
5: Size of CHR ROM in 8 KB units (Value 0 means the board uses CHR RAM)
6: Flags 6
7: Flags 7
8: Size of PRG RAM in 8 KB units (Value 0 infers 8 KB for compatibility; see PRG RAM circuit)
9: Flags 9
10: Flags 10 (unofficial)
11-15: Zero filled
*/
nes_cart::nes_cart(const char *filename)
{
    std::ifstream cartf;
    cartf.open(filename, ios::in | ios::binary);

    char header[16];
    cartf.read(header, ARRAYSIZE(header));
    if (memcmp(header, "NES\x1A", 4) != 0)
        throw std::runtime_error("Invalid NES file header");

    int prg_rom_num_16kb_banks = (int)header[4];
    if (prg_rom_num_16kb_banks != 1)
        throw std::runtime_error("Unhandled # of prg rom banks");
    cartf.read(prg_rom0_, ARRAYSIZE(prg_rom0_));
}

uint8_t
nes_cart::readu8(uint16_t address) const
{
    if (address >= 0x8000 && address <= 0xBFFF)
    {
        return prg_rom0_[address - 0x8000];
    }
    else if (address >= 0xC000 && address <= 0xFFFF)
    {
        return prg_rom0_[address - 0xC000];
    }
    else
    {
        assert(false);
        return 0;
    }
}

} // namespace cart
} // namespace deeznes