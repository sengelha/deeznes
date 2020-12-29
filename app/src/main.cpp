#include <SFML/Graphics.hpp>
#include <boost/format.hpp>
#include <console/nes_console.h>

namespace console = deeznes::console;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        throw std::runtime_error(
            (boost::format("Usage: %1% rom.nes") % argv[0]).str());
    }

    console::nes_console c;
    c.insert_cart(argv[1]);
    c.power_on();

    sf::RenderWindow mainwin(sf::VideoMode(640, 480), "deeznes");
    mainwin.setVerticalSyncEnabled(true);

    while (mainwin.isOpen()) {
        sf::Event event;
        while (mainwin.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mainwin.close();
        }

        c.run(1);
        if (c.should_render()) {
            mainwin.clear();
            c.render_to(mainwin);
            mainwin.display();
        }
    }

    return 0;
}