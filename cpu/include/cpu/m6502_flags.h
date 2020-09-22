#pragma once

namespace deeznes {
namespace cpu {

constexpr uint8_t carry_flag = 0x01;
constexpr uint8_t zero_flag = 0x02;
constexpr uint8_t disable_interrupts_flag = 0x04;
constexpr uint8_t decimal_flag = 0x08;
// See https://wiki.nesdev.com/w/index.php/CPU_status_flag_behavior
// for why these flags are named so strangely
constexpr uint8_t bit4_flag = 0x10;
constexpr uint8_t bit5_flag = 0x20;
constexpr uint8_t overflow_flag = 0x40;
constexpr uint8_t sign_flag = 0x80;

} // namespace cpu
} // namespace deeznes
