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
  // Boot is basically jmp ($FFFC) which is $C004
  ASSERT_EQ(0x04, cart.cpu_readu8(0xFFFC));
  ASSERT_EQ(0xC0, cart.cpu_readu8(0xFFFD));
  // Instructions start at $C000
  ASSERT_EQ(0x4C, cart.cpu_readu8(0xC000)); // $C000: JMP $C5F5
  ASSERT_EQ(0xF5, cart.cpu_readu8(0xC001));
  ASSERT_EQ(0xC5, cart.cpu_readu8(0xC002));
  ASSERT_EQ(0x60, cart.cpu_readu8(0xC003)); // $C003: RTS
  ASSERT_EQ(0x78, cart.cpu_readu8(0xC004)); // $C004: SEI
  ASSERT_EQ(0xD8, cart.cpu_readu8(0xC005)); // $C005: CLD

  // Test '0' tile of chr_rom
  ASSERT_EQ(0x3E, cart.ppu_readu8(0x0300));  // ..11111.
  ASSERT_EQ(0x63, cart.ppu_readu8(0x0301));  // .11...11
  ASSERT_EQ(0x67, cart.ppu_readu8(0x0302));  // .11..111
  ASSERT_EQ(0x6B, cart.ppu_readu8(0x0303));  // .11.1.11
  ASSERT_EQ(0x73, cart.ppu_readu8(0x0304));  // .111..11
  ASSERT_EQ(0x63, cart.ppu_readu8(0x0305));  // .11...11
  ASSERT_EQ(0x3E, cart.ppu_readu8(0x0306));  // ..11111.
  ASSERT_EQ(0x00, cart.ppu_readu8(0x0307));  // ........
  ASSERT_EQ(0x3E, cart.ppu_readu8(0x0308));
  ASSERT_EQ(0x63, cart.ppu_readu8(0x0309));
  ASSERT_EQ(0x67, cart.ppu_readu8(0x030A));
  ASSERT_EQ(0x6B, cart.ppu_readu8(0x030B));
  ASSERT_EQ(0x73, cart.ppu_readu8(0x030C));
  ASSERT_EQ(0x63, cart.ppu_readu8(0x030D));
  ASSERT_EQ(0x3E, cart.ppu_readu8(0x030E));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x030F));
}

TEST(ines_cart_tests, donkey_kong) {
  ines_cart cart("roms/donkey_kong.nes");
  ASSERT_EQ(0, cart.mapper_number());
  ASSERT_FALSE(cart.has_trainer());
  ASSERT_EQ(16384, cart.prg_rom_size());
  ASSERT_EQ(8192, cart.chr_rom_size());
  // Boot is basically jmp ($FFFC) which is $C79E
  ASSERT_EQ(0x9E, cart.cpu_readu8(0xFFFC));
  ASSERT_EQ(0xC7, cart.cpu_readu8(0xFFFD));
  // Instructions start at $C79E
  ASSERT_EQ(0x78, cart.cpu_readu8(0xC79E)); // $C79E: SEI
  ASSERT_EQ(0xD8, cart.cpu_readu8(0xC79F)); // $C79F: CLD

  // Test '0' tile of chr_rom
  ASSERT_EQ(0x38, cart.ppu_readu8(0x1000));  // ..111...
  ASSERT_EQ(0x4C, cart.ppu_readu8(0x1001));  // .1..11..
  ASSERT_EQ(0xC6, cart.ppu_readu8(0x1002));  // 11...11.
  ASSERT_EQ(0xC6, cart.ppu_readu8(0x1003));  // 11...11.
  ASSERT_EQ(0xC6, cart.ppu_readu8(0x1004));  // 11...11.
  ASSERT_EQ(0x64, cart.ppu_readu8(0x1005));  // .11..1..
  ASSERT_EQ(0x38, cart.ppu_readu8(0x1006));  // ..111...
  ASSERT_EQ(0x00, cart.ppu_readu8(0x1007));  // ........
  ASSERT_EQ(0x00, cart.ppu_readu8(0x1008));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x1009));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x100A));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x100B));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x100C));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x100D));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x100E));
  ASSERT_EQ(0x00, cart.ppu_readu8(0x100F));
}