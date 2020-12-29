#pragma once

#include "console_cpu_binder.h"
#include "console_ppu_binder.h"
#include "nes_console_state.h"
#include <SFML/Graphics.hpp>
#include <cart/nes_cart.h>
#include <cpu/m6502.h>
#include <io/nes_joystick.h>
#include <iostream>
#include <optional>
#include <ppu/ppu.h>

namespace deeznes {
namespace console {

class nes_console {
  private:
    uint8_t ram_[2048];
    friend class console_cpu_binder;
    console_cpu_binder cpu_binder_;
    deeznes::cpu::m6502 cpu_;
    friend class console_ppu_binder;
    console_ppu_binder ppu_binder_;
    deeznes::ppu::ppu ppu_;
    std::optional<deeznes::cart::nes_cart> cart_;
    std::optional<deeznes::io::nes_joystick> joy1_;
    std::optional<deeznes::io::nes_joystick> joy2_;
    uint8_t sound_regs_[19];
    uint8_t sound_switch_;
    bool power_on_;

  public:
    nes_console()
        : cpu_binder_(this), cpu_(&cpu_binder_), ppu_binder_(this),
          ppu_(&ppu_binder_), power_on_(false) {}

    void insert_cart(const char *filename);
    void power_on();
    uint_fast32_t run(uint_fast32_t maxcycles);
    void set_state(const nes_console_state &state);
    nes_console_state state() const;

    bool should_draw() const;
    void draw_to(sf::RenderTarget &tgt);

    friend std::ostream &operator<<(std::ostream &os,
                                    const nes_console &console);
};

std::ostream &operator<<(std::ostream &os, const nes_console &console);

} // namespace console
} // namespace deeznes
