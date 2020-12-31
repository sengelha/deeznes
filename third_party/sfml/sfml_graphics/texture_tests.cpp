#include <SFML/Graphics/Texture.hpp>
#include <gtest/gtest.h>

TEST(texture_tests, basics) {
    sf::Texture t;
    t.create(800, 600);
    ASSERT_EQ(sf::Vector2u(800, 600), t.getSize());
}