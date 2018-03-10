#include <gtest/gtest.h>
#include <set>
#include "lib/bst.h"

TEST(BST, DEFAULT_CONSTRUCTOR_TEST) {
    tlib::bst<int> input;
    ASSERT_EQ(0, input.size());
}