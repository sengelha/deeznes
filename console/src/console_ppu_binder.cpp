#include <console/console_ppu_binder.h>
#include <console/nes_console.h>

namespace deeznes {
namespace console {

void console_ppu_binder::vblank_nmi() {
    console_->cpu_.nmi(0xFFFA);
}

} // namespace console
} // namespace deeznes