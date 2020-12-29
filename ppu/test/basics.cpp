#include <gtest/gtest.h>
#include <ppu/ppu.h>
#include <gmock/gmock.h>

using namespace deeznes::ppu;
using ::testing::Exactly;

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

TEST(ppu_basics, issues_vblank_nmi) {
  class MockPpuCallback : public ppu_callbacks
  {
  public:
    MOCK_METHOD0(vblank_nmi, void());
  };

  ppu_state state;
  state.regs.ppuctrl = CTRL1_VBLANK_ENABLE;
  state.scanline = 241;
  state.cycles = 1;

  MockPpuCallback cb;
  EXPECT_CALL(cb, vblank_nmi())
    .Times(Exactly(1));
  ppu ppu(&cb);
  ppu.set_state(state);
  ppu.run(1);
}