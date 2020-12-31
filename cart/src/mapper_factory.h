#pragma once

#include <cart/mapper.h>
#include <compat/span.h>
#include <memory>

namespace deeznes {
namespace cart {

class mapper_factory {
  public:
    static std::unique_ptr<mapper> create(int mapper_number,
                                          std::span<const char> prg_rom,
                                          std::span<const char> chr_rom);
};

} // namespace cart
} // namespace deeznes
