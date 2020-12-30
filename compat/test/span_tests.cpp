#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <compat/span.h>

using ::testing::ElementsAre;

TEST(span_tests, ptr_len_constructor) {
    int a[]{44, -15, 45, 67, 89, 66};
    std::span<int> s1{a, std::size(a)};
    ASSERT_THAT(s1, ElementsAre(44, -15, 45, 67, 89, 66));

}

TEST(span_tests, array_constructor) {
    int a[]{44, -15, 45, 67, 89, 66};
    std::span<int> s1{a};
    ASSERT_THAT(s1, ElementsAre(44, -15, 45, 67, 89, 66));
}

TEST(span_tests, size) {
    int a[]{44, -15, 45, 67, 89, 66};
    std::span<int> s1{a};
    ASSERT_EQ(6, s1.size());
}

TEST(span_tests, subscript) {
    int a[]{44, -15, 45, 67, 89, 66};
    std::span<int> s1{a};
    ASSERT_EQ(45, s1[2]);
}

