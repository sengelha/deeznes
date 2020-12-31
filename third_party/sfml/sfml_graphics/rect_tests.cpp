#include <SFML/Graphics/Rect.hpp>
#include <gtest/gtest.h>

TEST(rect_tests, basics) {
    sf::Rect<int> r(5, 10, 20, 30);
    ASSERT_TRUE(r.contains(15, 15));
}