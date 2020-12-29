#include <console/console_cpu_binder.h>
#include <console/nes_console.h>
#include <boost/format.hpp>

using namespace std;

namespace deeznes {
namespace console {

uint8_t console_cpu_binder::readu8(uint16_t address) const {
  if (address < 0x0800) {
    return console_->ram_[address];
  } else if (address >= 0x0800 && address < 0x1000) {
    return console_->ram_[address - 0x0800];
  } else if (address >= 0x1000 && address < 0x1800) {
    return console_->ram_[address - 0x1000];
  } else if (address >= 0x1800 && address < 0x2000) {
    return console_->ram_[address - 0x1800];
  } else if (address == 0x2002) {
    return console_->ppu_.status();
  } else if (address == 0x2007) {
    return console_->ppu_.ppudata();
  } else if (address >= 0x4000 && address <= 0x4013) {
    return console_->sound_regs_[address - 0x4000];
  } else if (address == 0x4015) {
    return console_->sound_switch_;
  } else if (address == 0x4017) {
    return console_->joy2_->reg;
  } else if (address >= 0x8000 && address <= 0xFFFF &&
             console_->cart_) {
    return console_->cart_->readu8(address);
  } else {
    throw std::runtime_error(
      (boost::format("Unable to read from address $%04X") % address).str());
  }
}

void console_cpu_binder::writeu8(uint16_t address, uint8_t val) {
  if (address < 0x0800) {
    console_->ram_[address] = val;
  } else if (address == 0x2000) {
    console_->ppu_.set_ctrl(val);
  } else if (address == 0x2001) {
    console_->ppu_.set_mask(val);
  } else if (address == 0x2005) {
    console_->ppu_.set_scroll(val);
  } else if (address == 0x2006) {
    console_->ppu_.set_ppuaddr(val);
  } else if (address == 0x2007) {
    console_->ppu_.set_ppudata(val);
  } else if (address >= 0x4000 && address <= 0x4013) {
    console_->sound_regs_[address - 0x4000] = val;
  } else if (address == 0x4015) {
    console_->sound_switch_ = val;
  } else if (address == 0x4017) {
    console_->joy2_->reg = val;
  } else if (address >= 0x4020 && address <= 0xFFFF &&
             console_->cart_) {
    console_->cart_->writeu8(address, val);
  } else {
    throw std::runtime_error(
      (boost::format("Unable to write to address $%04X") % address).str());
  }
}

} // namespace console
} // namespace deeznes