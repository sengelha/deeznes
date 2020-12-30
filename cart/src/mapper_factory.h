#pragma once

#include <cart/cart_data.h>
#include <cart/mapper.h>
#include <compat/span.h>
#include <memory>

namespace deeznes {
namespace cart {

class mapper_factory {
  public:
    static std::unique_ptr<mapper> create(int mapper_number,
                                          std::span<uint8_t> prg_rom,
                                          std::span<uint8_t> chr_rom);
};

} // namespace cart
} // namespace deeznes
