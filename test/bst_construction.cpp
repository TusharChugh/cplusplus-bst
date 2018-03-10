#include <gtest/gtest.h>
#include <set>
#include "lib/bst.h"

TEST(BST, DEFAULT_CONSTRUCTOR_SIZE_TEST) {
    tlib::bst<int> input;
    ASSERT_EQ(0, input.size());
}

TEST(BST, DEFAULT_CONSTRUCTOR_EMPTY_TEST) {
    tlib::bst<int> input;
    ASSERT_TRUE(input.empty());
}