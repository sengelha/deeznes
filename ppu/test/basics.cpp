#include <gtest/gtest.h>
#include <ppu/ppu.h>

using namespace deeznes::ppu;

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

TEST(ppu_basics, poweron_state) {
  ppu ppu(nullptr);
  ASSERT_EQ(0, ppu.state().regs.ppuctrl);
  ASSERT_EQ(0, ppu.state().regs.ppumask);
  ASSERT_EQ(0, ppu.state().regs.ppustatus);
  ASSERT_EQ(0, ppu.state().regs.ppuaddr);
  ASSERT_EQ(0, ppu.state().regs.ppudata);
  ASSERT_EQ(0, ppu.state().cycles);
  ASSERT_EQ(0, ppu.state().scanline);
}