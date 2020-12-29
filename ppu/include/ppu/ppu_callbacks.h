#pragma once

namespace deeznes {
namespace ppu {

class ppu_callbacks {
public:
  virtual ~ppu_callbacks() = default;
  virtual void vblank_nmi() = 0;
};

} // namespace ppu
} // namespace deeznes
