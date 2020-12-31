#include <SFML/Window/Window.hpp>
#include <gtest/gtest.h>

TEST(window_tests, basics) {
    sf::Window w;
    ASSERT_FALSE(w.isOpen());
}