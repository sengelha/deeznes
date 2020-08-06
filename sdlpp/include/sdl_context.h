#pragma once

#include <stdexcept>
#include <boost/format.hpp>
#include <SDL2/SDL.h>
#include <sdlpp/non_copyable.h>

namespace deeznes
{
namespace sdlpp
{

class sdl_context : non_copyable
{
public:
	sdl_context(Uint32 flags)
	{
		if (SDL_Init(flags) != 0)
		{
			throw std::runtime_error((boost::format("Unable to initialize SDL: %1%") % SDL_GetError()).str());
		}
	}

	~sdl_context()
	{
		SDL_Quit();
	}
};

} // namespace sdl
} // namespace deeznes