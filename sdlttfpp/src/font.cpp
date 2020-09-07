#include <boost/format.hpp>
#include <sdlttfpp/font.h>
#include <stdexcept>

namespace deeznes {
namespace sdlttfpp {

font::font(const char *file, int ptsize) {
    m_font = TTF_OpenFont(file, ptsize);
    if (!m_font) {
        throw std::runtime_error(
            (boost::format("Unable to open font %1% :%2%") % file %
             TTF_GetError())
                .str());
    }
}

font::~font() {
    if (m_font) {
        TTF_CloseFont(m_font);
    }
}

sdlpp::surface font::render_text_solid(const std::string &text, SDL_Color fg) {
    SDL_Surface *s = TTF_RenderText_Solid(m_font, text.c_str(), fg);
    if (!s) {
        throw std::runtime_error(
            (boost::format("Unable to render text: %1%") % TTF_GetError())
                .str());
    }
    return sdlpp::surface(s);
}

sdlpp::surface font::render_text_shaded(const std::string &text, SDL_Color fg,
                                        SDL_Color bg) {
    SDL_Surface *s = TTF_RenderText_Shaded(m_font, text.c_str(), fg, bg);
    if (!s) {
        throw std::runtime_error(
            (boost::format("Unable to render text: %1%") % TTF_GetError())
                .str());
    }
    return sdlpp::surface(s);
}

std::tuple<int, int> font::size_text(const std::string &text) {
    int w;
    int h;
    if (TTF_SizeText(m_font, text.c_str(), &w, &h) != 0) {
        throw std::runtime_error(
            (boost::format("Unable to size text: %1%") % TTF_GetError()).str());
    }
    return std::make_tuple(w, h);
}

} // namespace sdlttfpp
} // namespace deeznes