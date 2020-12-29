#include <SFML/Graphics.hpp>
#include <boost/format.hpp>
#include <console/nes_console.h>
#include "cpu_display.h"
#include "instr_display.h"

namespace app = deeznes::app;
namespace console = deeznes::console;

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

    while (w.isOpen()) {
        sf::Event event;
        while (w.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                w.close();
        }

        c.run(1);
        instrDisplay.update();

        w.clear();
        w.draw(cpuDisplay);
        w.draw(instrDisplay);
        w.display();
    }

    return 0;
}