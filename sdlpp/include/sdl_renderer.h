#pragma once

#include <stdexcept>
#include <boost/format.hpp>
#include <SDL2/SDL.h>
#include <sdlpp/non_copyable.h>
#include <sdlpp/sdl_surface.h>
#include <sdlpp/sdl_texture.h>

namespace deeznes
{
namespace sdlpp
{

class sdl_renderer : non_copyable
{
private:
	SDL_Renderer* ren_;

public:
	sdl_renderer(SDL_Window* win, int index, Uint32 flags)
	{
		ren_ = SDL_CreateRenderer(win, index, flags);
		if (ren_ == nullptr) {
			throw std::runtime_error((boost::format("Unable to create renderer: %1%") % SDL_GetError()).str());
		}
	}

	void clear()
	{
		SDL_RenderClear(ren_);
	}

	void copy(const sdl_texture& texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect)
	{
		SDL_RenderCopy(ren_, texture.get(), srcrect, dstrect);
	}

	void present()
	{
		SDL_RenderPresent(ren_);
	}

	sdl_texture create_texture_from_surface(const sdl_surface& surface) {
		return sdl_texture(ren_, surface.get());
	}

	~sdl_renderer()
	{
		SDL_DestroyRenderer(ren_);
	}
};

} // namespace sdl
} // namespace deeznes