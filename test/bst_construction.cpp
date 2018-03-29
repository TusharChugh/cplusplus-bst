#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include "lib/bst.h"

TEST( BST, DEFAULT_CONSTRUCTOR_SIZE_TEST ) {
    tlib::bst<int> input;
    ASSERT_EQ( static_cast<uint8_t>( 0 ), input.size() );
}

TEST( BST, DEFAULT_CONSTRUCTOR_EMPTY_TEST ) {
    tlib::bst<int> input;
    ASSERT_TRUE( input.empty() );
}

TEST( BST, CONSTRUCTIONS_LVALUE_UNIQUE_TEST ) {
    tlib::bst<int> input;
    ASSERT_EQ( 0, input.size() );
    ASSERT_TRUE( input.empty() );
    const int a = 10;
    const int b = 20;
    const int c = 30;
    ASSERT_EQ( *( input.insert( a ).first ), 10 );
    ASSERT_EQ( *( input.insert( b ).first ), 20 );
    ASSERT_EQ( *( input.insert( c ).first ), 30 );
    ASSERT_EQ( 3, input.size() );
    ASSERT_FALSE( input.empty() );
}

TEST( BST, CONSTRUCTIONS_RVALUE_UNIQUE_TEST ) {
    tlib::bst<int> input;
    ASSERT_EQ( 0, input.size() );
    ASSERT_TRUE( input.empty() );
    ASSERT_EQ( *( input.insert( 10 ).first ), 10 );
    ASSERT_EQ( *( input.insert( 20 ).first ), 20 );
    ASSERT_EQ( *( input.insert( 30 ).first ), 30 );
    // ASSERT_EQ( 3, input.size() );
    ASSERT_FALSE( input.empty() );
}
