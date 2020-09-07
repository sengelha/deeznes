#include "cpu_win.h"
#include "main_win.h"
#include <boost/format.hpp>
#include <console/nes_console.h>
#include <iostream>
#include <sdlpp/sdlpp.h>
#include <sdlttfpp/sdlttfpp.h>
#include <vector>

namespace console = deeznes::console;
namespace sdl = deeznes::sdlpp;
namespace sdlttf = deeznes::sdlttfpp;
namespace app = deeznes::app;

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            throw std::runtime_error(
                (boost::format("Usage: %1% rom.nes") % argv[0]).str());
        }

        console::nes_console c;
        c.insert_cart(argv[1]);
        c.power_on();

        sdl::init_ctxt sdl_ctxt(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        sdlttf::init_ctxt ttf_ctxt;

        app::main_win main_win;
        app::cpu_win cpu_win(&c, 800, 100, 350, 80);
        std::vector<window *> windows;
        windows.push_back(&main_win);
        windows.push_back(&cpu_win);

        while (1) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    return 0;
                }

                /*
                for (auto& w : windows) {
                  w.handle_event(e);
                }
                */

                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        return 0;
                    }
                }
            }

            c.run(1);
            for (auto &w : windows) {
                w->render();
            }
        }

        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}