#pragma once

#include <cart/mapper.h>
#include <compat/span.h>
#include <cstdint>

namespace deeznes {
namespace cart {

class nrom_mapper : public mapper {
  private:
    std::span<const char> prg_rom_;
    std::span<const char> chr_rom_;

  public:
    nrom_mapper(std::span<const char> prg_rom, std::span<const char> chr_rom)
        : prg_rom_(prg_rom), chr_rom_(chr_rom) {}
    virtual uint8_t cpu_readu8(uint16_t addr) const override final;
    virtual uint8_t ppu_readu8(uint16_t addr) const override final;
};

} // namespace cart
} // namespace deeznes
