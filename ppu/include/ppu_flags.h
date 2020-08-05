#pragma once

#include <stdint.h>

namespace deeznes
{
namespace ppu
{

static const uint8_t CTRL1_VBLANK_ENABLE = 0x80;
static const uint8_t STATUS_VBLANK_FLAG = 0x80;

} // namespace ppu
} // namespace deeznes