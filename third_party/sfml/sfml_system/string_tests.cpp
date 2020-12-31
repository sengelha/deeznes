#include <SFML/System/String.hpp>
#include <gtest/gtest.h>

TEST(string_tests, basics) {
    sf::String s("hello");
    ASSERT_EQ("hello", s);
}