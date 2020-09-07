#pragma once

#include <SDL_ttf.h>
#include <boost/core/noncopyable.hpp>

namespace deeznes {
namespace sdlttfpp {

class init_ctxt : private boost::noncopyable {
  public:
    init_ctxt() {
        if (TTF_Init() != 0) {
            throw std::runtime_error(
                (boost::format("Unable to initialize SDL_ttf: %1%") %
                 TTF_GetError())
                    .str());
        }
    }

    ~init_ctxt() { TTF_Quit(); }
};

} // namespace sdlttfpp
} // namespace deeznes