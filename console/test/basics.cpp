#include <gtest/gtest.h>
#include <console/nes_console.h>
#include <gmock/gmock.h>

using namespace deeznes::cart;
using namespace deeznes::console;
using namespace deeznes::ppu;
using ::testing::Return;

TEST(console_basics, vblank_nmi) {
  class MockNesCart : public nes_cart
  {
  public:
    MOCK_CONST_METHOD1(readu8, uint8_t(uint16_t));
    MOCK_METHOD2(writeu8, void(uint16_t, uint8_t));
  };
  MockNesCart cart;
  EXPECT_CALL(cart, readu8(0xC000)).WillRepeatedly(Return(0x02)); // NOPIMP
  EXPECT_CALL(cart, readu8(0xFFFA)).WillRepeatedly(Return(0x34));
  EXPECT_CALL(cart, readu8(0xFFFB)).WillRepeatedly(Return(0x12));

  nes_console console;
  console.insert_cart(&cart);

  nes_console_state state;
  state.cpu_state.regs.PC = 0xC000;
  state.cpu_state.regs.S = 0xFF;
  state.cpu_state.cycles = 0;
  state.ppu_state.regs.ppuctrl = CTRL1_VBLANK_ENABLE;
  state.ppu_state.scanline = 241;
  state.ppu_state.cycles = 1;
  console.set_state(state);
  console.run(1);

  nes_console_state after_state = console.state();
  ASSERT_EQ(0xFC, after_state.cpu_state.regs.S);
  ASSERT_EQ(0x1234, after_state.cpu_state.regs.PC);
  ASSERT_EQ(2, after_state.cpu_state.cycles);
  ASSERT_EQ(0xC0, console.cpu_readu8(0x01FF));
  ASSERT_EQ(0x01, console.cpu_readu8(0x01FE));
  ASSERT_EQ(0xFD, console.cpu_readu8(0x01FD));
}