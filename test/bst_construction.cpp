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

TEST(BST, CONSTRUCTIONS_CONFIG1_TEST) {
    tlib::bst<int> input;
    std::cout<<"Test insertion "<<*(input.insert(20).first)<<std::endl;
    std::cout<<"Test insertion "<<*(input.insert(10).first)<<std::endl;
    std::cout<<"Test insertion "<<*(input.insert(15).first)<<std::endl;
    
    ASSERT_FALSE(input.empty());
    ASSERT_EQ(3, input.size());
}