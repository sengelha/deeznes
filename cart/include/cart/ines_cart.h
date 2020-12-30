#pragma once

#include <cart/cart_data.h>
#include <cart/nes_cart.h>
#include <cart/mapper.h>
#include <libc/unique_fd.h>
#include <memory>

namespace deeznes {
namespace cart {

class ines_cart : public nes_cart {
private:
  deeznes::libc::unique_fd fd_;
  uint8_t* cart_;
  off_t size_;
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
