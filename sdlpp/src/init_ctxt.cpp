#include <boost/format.hpp>
#include <sdlpp/init_ctxt.h>
#include <stdexcept>

namespace deeznes {
namespace sdlpp {

init_ctxt::init_ctxt(Uint32 flags) {
    if (SDL_Init(flags) != 0) {
        throw std::runtime_error(
            (boost::format("Unable to initialize SDL: %1%") % SDL_GetError())
                .str());
    }
}

init_ctxt::~init_ctxt() { SDL_Quit(); }

} // namespace sdlpp
} // namespace deeznes