#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cart/ines_cart.h>

using namespace deeznes::cart;
using ::testing::ElementsAre;

TEST(ines_cart_tests, nestest) {
  ines_cart cart("roms/nestest.nes");
  ASSERT_EQ(0, cart.mapper_number());
  ASSERT_FALSE(cart.has_trainer());
  ASSERT_EQ(16384, cart.prg_rom_size());
  ASSERT_EQ(8192, cart.chr_rom_size());
  // First instructions in prg rom are JMP 0xC5F5
  ASSERT_EQ(0x4C, cart.cpu_readu8(0xC000));
  ASSERT_EQ(0xF5, cart.cpu_readu8(0xC001));
  ASSERT_EQ(0xC5, cart.cpu_readu8(0xC002));
  // Test first tile of chr_rom
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0000));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0001));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0002));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0003));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0004));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0005));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0006));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0007));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0008));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0009));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x000A));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x000B));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x000C));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x000D));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x000E));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x000F));
}