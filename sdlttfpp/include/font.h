#pragma once

#include <SDL_ttf.h>
#include <boost/core/noncopyable.hpp>
#include <sdlpp/sdlpp.h>
#include <string_view>

namespace deeznes {
namespace sdlttfpp {

class font : private boost::noncopyable {
  private:
    TTF_Font *m_font;

  public:
    font(const char *file, int ptsize);
    sdlpp::surface render_text_solid(const std::string &text, SDL_Color fg);
    sdlpp::surface render_text_shaded(const std::string &text, SDL_Color fg,
                                      SDL_Color bg);
    std::tuple<int, int> size_text(const std::string &text);
};

} // namespace sdlttfpp
} // namespace deeznes