#include <console/console_ppu_binder.h>
#include <console/nes_console.h>
#include <boost/format.hpp>

namespace deeznes {
namespace console {

void console_ppu_binder::vblank_nmi() {
    console_->cpu_.nmi(0xFFFA);
}

uint8_t console_ppu_binder::readu8(uint16_t address) const {
    if (address >= 0x0000 && address <= 0x0FFF) {
        return console_->cart_->ppu_readu8(address);
    } else {
        std::cerr << boost::format("WARNING: PPU unable to read from address $%04X") % address << "\n";
        return 0;
    }
}

} // namespace console
} // namespace deeznes