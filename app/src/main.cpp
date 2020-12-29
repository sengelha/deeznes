#include <SFML/Graphics.hpp>
#include <boost/format.hpp>
#include <console/nes_console.h>
#include "cpu_display.h"
#include "instr_display.h"

namespace app = deeznes::app;
namespace console = deeznes::console;

const int RENDER_STEP_COUNT = 1000;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        throw std::runtime_error(
            (boost::format("Usage: %1% rom.nes") % argv[0]).str());
    }

    console::nes_console c;
    c.insert_cart(argv[1]);
    c.power_on();

    sf::RenderWindow w(sf::VideoMode(1700, 1200), "deeznes");
    //w.setVerticalSyncEnabled(true);

    app::cpu_display cpuDisplay(c);
    cpuDisplay.setPosition(1300, 0);

    app::instr_display instrDisplay(c);
    instrDisplay.setPosition(0, 890);

    bool paused = false;
    bool step = false;
    int render_counter = RENDER_STEP_COUNT;

    while (w.isOpen()) {
        sf::Event event;
        while (w.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                w.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Space:
                    paused = !paused;
                    break;
                case sf::Keyboard::Escape:
                case sf::Keyboard::Q:
                    w.close();
                    break;
                case sf::Keyboard::S:
                    paused = true;
                    step = true;
                    break;
                default:
                    // Do nothing
                    break;
                }
                break;
            default:
                // Do nothing
                break;
            }
        }

        if (step || !paused)
        {
            c.run(1);
            instrDisplay.update();
            step = false;
        }

        if (--render_counter == 0)
        {
            w.clear();
            w.draw(cpuDisplay);
            w.draw(instrDisplay);
            w.display();
            render_counter = RENDER_STEP_COUNT;
        }
    }

    return 0;
}