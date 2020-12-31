#include <SFML/Graphics/RenderWindow.hpp>
#include <gtest/gtest.h>

TEST(renderwindow_tests, basics) {
    sf::RenderWindow w(sf::VideoMode(800, 600), "test");
    ASSERT_EQ(w.getSize(), sf::Vector2u(800, 600));
}