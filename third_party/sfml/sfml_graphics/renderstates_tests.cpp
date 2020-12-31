#include <SFML/Graphics/RenderStates.hpp>
#include <gtest/gtest.h>

TEST(renderstates_tests, basics) {
    sf::RenderStates rs;
    sf::BlendMode expected;
    ASSERT_EQ(expected, rs.blendMode);
}