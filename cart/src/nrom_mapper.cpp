// https://wiki.nesdev.com/w/index.php/NROM
#include "nrom_mapper.h"
#include <boost/format.hpp>
#include <iostream>
#include <stdexcept>

namespace deeznes {
namespace cart {

uint8_t nrom_mapper::cpu_readu8(uint16_t addr) const {
    if (addr >= 0x8000 && addr <= 0xBFFF) {
        return prg_rom_[addr - 0x8000];
    } else if (addr >= 0xC000 && addr <= 0xFFFF && prg_rom_.size() == 16384) {
        return prg_rom_[addr - 0xC000];
    } else if (addr >= 0xC000 && addr <= 0xFFFF && prg_rom_.size() == 32768) {
        return prg_rom_[addr];
    } else {
        std::cerr
            << boost::format(
                   "WARNING: NROM mapper unable to read CPU address $%04X") %
                   addr
            << "\n";
        return 0;
    }
}

uint8_t nrom_mapper::ppu_readu8(uint16_t addr) const {
    if (addr >= 0x000 && addr <= 0x1FFF && addr < chr_rom_.size()) {
        return chr_rom_[addr];
    } else {
        std::cerr
            << boost::format(
                   "WARNING: NROM mapper unable to read PPU address $%04X") %
                   addr
            << "\n";
        return 0;
    }
}

} // namespace cart
} // namespace deeznes