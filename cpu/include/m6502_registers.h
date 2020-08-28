#pragma once

#include <cstdint>

namespace deeznes {
namespace cpu {

struct m6502_registers {
  std::uint8_t A;
  std::uint8_t P;
  std::uint8_t X;
  std::uint8_t Y;
  std::uint8_t S;
  std::uint16_t PC;
};

} // namespace cpu
} // namespace deeznes