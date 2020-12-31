#include <SFML/Graphics.hpp>
#include <boost/format.hpp>
#include <cart/ines_cart.h>
#include <console/nes_console.h>
#include "cpu_display.h"
#include "instr_display.h"
#include "pat_table_display.h"

namespace app = deeznes::app;
namespace cart = deeznes::cart;
namespace console = deeznes::console;

const int CYCLE_BATCH_SIZE = 1000;
const int RENDER_STEP_COUNT = 10000;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        throw std::runtime_error(
            (boost::format("Usage: %1% rom.nes") % argv[0]).str());
    }

    cart::ines_cart cart(argv[1]);

    console::nes_console c;
    c.insert_cart(&cart);
    c.power_on();

    sf::RenderWindow w(sf::VideoMode(1800, 1600), "deeznes");
    //w.setVerticalSyncEnabled(true);

    app::cpu_display cpuDisplay(c);
    cpuDisplay.setPosition(1500, 0);

    app::instr_display instrDisplay(c);
    instrDisplay.setPosition(0, 1200);

    app::pat_table_display patTableDisplay(c);
    patTableDisplay.setPosition(0, 600);
    patTableDisplay.setScale(4, 4);

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
            c.run(step ? 1 : CYCLE_BATCH_SIZE);
            instrDisplay.update();
            step = false;
        }

        if (--render_counter == 0)
        {
            w.clear();
            w.draw(cpuDisplay);
            w.draw(instrDisplay);
            w.draw(patTableDisplay);
            w.display();
            render_counter = RENDER_STEP_COUNT;
        }
    }

    return 0;
}