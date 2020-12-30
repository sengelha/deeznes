#include <cart/ines_cart.h>
#include <libc/fstat.h>
#include <libc/mmap.h>
#include <libc/open.h>
#include <libc/sysconf.h>
#include "mapper_factory.h"

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif

static constexpr int round_up(int n, int multiple) {
  return ((n + multiple - 1) / multiple) * multiple;
}

namespace deeznes {
namespace cart {

/*
An iNES file consists of the following sections, in order:
1. Header (16 bytes)
2. Trainer, if present (0 or 512 bytes)
3. PRG ROM data (16384 * x bytes)
4. CHR ROM data, if present (8192 * y bytes)
5. PlayChoice INST-ROM, if present (0 or 8192 bytes)
6. PlayChoice PROM, if present (16 bytes Data, 16 bytes CounterOut) (this is
often missing, see PC10 ROM-Images for details)
7. Occassionally, a 128-byte (or sometimes 127-byte) title at the end of the
file.

The format of the header is as follows:
0-3: Constant $4E $45 $53 $1A ("NES" followed by MS-DOS end-of-file)
4: Size of PRG ROM in 16 KB units
5: Size of CHR ROM in 8 KB units (Value 0 means the board uses CHR RAM)
6: Flags 6
7: Flags 7
8: Size of PRG RAM in 8 KB units (Value 0 infers 8 KB for compatibility; see PRG
RAM circuit) 9: Flags 9 10: Flags 10 (unofficial) 11-15: Zero filled
*/
ines_cart::ines_cart(const char *filename)
{
  fd_ = libc::open(filename, O_RDONLY, 0);
  struct stat si;
  libc::fstat(fd_.get(), &si);
  cart_ = (uint8_t*)libc::mmap(NULL, round_up(si.st_size, libc::sysconf(_SC_PAGESIZE)), PROT_READ, MAP_FILE | MAP_SHARED, fd_.get(), 0);
  if (memcmp(cart_, "NES\x1A", 4) != 0)
    throw std::runtime_error("Invalid NES file header");
  size_ = si.st_size;

  size_t prg_rom_size = 16384 * cart_[4];
  std::span<uint8_t> prg_rom(cart_ + 16, prg_rom_size);
  size_t chr_rom_size = 8192 * cart_[5];
  std::span<uint8_t> chr_rom(cart_ + 16 + prg_rom_size, chr_rom_size);
  mapper_ = mapper_factory::create((cart_[7] & 0xF0) | (cart_[6] >> 4), prg_rom, chr_rom);
}

bool ines_cart::has_trainer() const {
  return (cart_[6] & 0x04);
}

int ines_cart::mapper_number() const {
  return (cart_[7] & 0xF0) | (cart_[6] >> 4);
}

int ines_cart::prg_rom_size() const {
  return 16384 * cart_[4];
}

int ines_cart::chr_rom_size() const {
  return 8192 * cart_[5];
}

uint8_t ines_cart::cpu_readu8(uint16_t offset) const {
  return mapper_->cpu_readu8(offset);
}

uint8_t ines_cart::ppu_readu8(uint16_t offset) const {
  return mapper_->ppu_readu8(offset);
}

} // namespace cart
} // namespace deeznes