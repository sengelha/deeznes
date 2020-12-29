#include <console/console_ppu_binder.h>
#include <stdexcept>

namespace deeznes {
namespace console {

void console_ppu_binder::vblank_nmi() {
    throw std::runtime_error("TODO");
}

} // namespace console
} // namespace deeznes