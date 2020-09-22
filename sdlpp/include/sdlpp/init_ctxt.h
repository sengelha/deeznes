#pragma once

#include <SDL2/SDL.h>
#include <boost/core/noncopyable.hpp>

namespace deeznes {
namespace sdlpp {

class init_ctxt : private boost::noncopyable {
  public:
    init_ctxt(Uint32 flags);
    ~init_ctxt();
};

} // namespace sdlpp
} // namespace deeznes