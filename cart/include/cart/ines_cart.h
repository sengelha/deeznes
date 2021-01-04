#pragma once

#include <boost/iostreams/device/mapped_file.hpp>
#include <cart/mapper.h>
#include <cart/nes_cart.h>
#include <memory>

namespace deeznes {
namespace cart {

class ines_cart : public nes_cart {
  private:
    boost::iostreams::mapped_file_source file_;
    std::unique_ptr<mapper> mapper_;

  public:
    ines_cart(const char *filename);
    bool has_trainer() const;
    int mapper_number() const;
    int prg_rom_size() const;
    int chr_rom_size() const;
    uint8_t cpu_readu8(uint16_t addr) const override final;
    uint8_t ppu_readu8(uint16_t addr) const override final;
};

} // namespace cart
} // namespace deeznes
