#include "mapper_factory.h"
#include "nrom_mapper.h"
#include <memory>
#include <stdexcept>

namespace deeznes {
namespace cart {

std::unique_ptr<mapper> mapper_factory::create(int mapper_number,
                                               std::span<uint8_t> prg_rom,
                                               std::span<uint8_t> chr_rom) {
    switch (mapper_number) {
    case 0:
        return std::make_unique<nrom_mapper>(prg_rom, chr_rom);
    default:
        throw std::runtime_error("Unrecognized mapper number");
    }
}

} // namespace cart
} // namespace deeznes