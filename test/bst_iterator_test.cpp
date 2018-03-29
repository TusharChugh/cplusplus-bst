#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include "lib/bst.h"

TEST( BST, ITERATOR_BEGIN_TEST ) {
    tlib::bst<int> input;
    ASSERT_EQ( 0, input.size() );
    ASSERT_TRUE( input.empty() );
    const int a = 10;
    const int b = 20;
    const int c = 30;
    ASSERT_EQ( *( input.insert( a ).first ), a );
    ASSERT_EQ( *( input.insert( b ).first ), b );
    ASSERT_EQ( *( input.insert( c ).first ), c );
    ASSERT_EQ( *input.begin(), a );
    ASSERT_EQ( 3, input.size() );
    ASSERT_FALSE( input.empty() );
}

TEST( BST, ITERATOR_PREINCREMENT1_TEST ) {
    tlib::bst<int> input;
    ASSERT_EQ( 0, input.size() );
    ASSERT_TRUE( input.empty() );
    const int a = 10;
    const int b = 20;
    const int c = 30;
    ASSERT_EQ( *( input.insert( a ).first ), a );
    ASSERT_EQ( *( input.insert( b ).first ), b );
    ASSERT_EQ( *( input.insert( c ).first ), c );
    auto it = input.begin();
    ASSERT_EQ( *( ++it ), b );
    ASSERT_EQ( *( ++it ), c );
    ASSERT_EQ( 3, input.size() );
    ASSERT_FALSE( input.empty() );
}

TEST( BST, ITERATOR_POSTINCREMENT1_TEST ) {
    tlib::bst<int> input;
    ASSERT_EQ( 0, input.size() );
    ASSERT_TRUE( input.empty() );
    const int a = 10;
    const int b = 20;
    const int c = 30;
    ASSERT_EQ( *( input.insert( a ).first ), a );
    ASSERT_EQ( *( input.insert( b ).first ), b );
    ASSERT_EQ( *( input.insert( c ).first ), c );
    auto it = input.begin();
    ASSERT_EQ( *( it++ ), a );
    ASSERT_EQ( *( it++ ), b );
    ASSERT_EQ( *( it ), c );
    ASSERT_EQ( 3, input.size() );
    ASSERT_FALSE( input.empty() );
}

TEST( BST, ITERATOR_END_TEST ) {
    tlib::bst<int> input;
    ASSERT_EQ( 0, input.size() );
    ASSERT_TRUE( input.empty() );
    const int a = 10;
    const int b = 20;
    const int c = 30;
    ASSERT_EQ( *( input.insert( a ).first ), a );
    ASSERT_EQ( *( input.insert( b ).first ), b );
    ASSERT_EQ( *( input.insert( c ).first ), c );
    auto it = ++input.begin();
    ASSERT_EQ( *( it ), b );
    ASSERT_EQ( *( ++it ), c );
    ASSERT_EQ( 3, input.size() );
    ASSERT_FALSE( input.empty() );
}

TEST( BST, ITERATOR_END2_TEST ) {
    tlib::bst<int> input;
    ASSERT_EQ( 0, input.size() );
    ASSERT_TRUE( input.empty() );
    const int a = 20;
    const int b = 10;
    const int c = 30;
    ASSERT_EQ( *( input.insert( a ).first ), a );
    ASSERT_EQ( *( input.insert( b ).first ), b );
    ASSERT_EQ( *( input.insert( c ).first ), c );
    auto it = input.begin();
    ASSERT_EQ( *( it ), b );
    ASSERT_EQ( *( ++it ), a );
    ASSERT_EQ( *( ++it ), c );
    ASSERT_EQ( 3, input.size() );
    ASSERT_FALSE( input.empty() );
}

TEST( BST, ITERATOR_EQUAL_OPERATOR_TEST ) {
    tlib::bst<int> input;
    ASSERT_EQ( 0, input.size() );
    ASSERT_TRUE( input.empty() );
    const int a = 10;
    const int b = 20;
    const int c = 30;
    ASSERT_EQ( *( input.insert( a ).first ), a );
    ASSERT_EQ( *( input.insert( b ).first ), b );
    ASSERT_EQ( *( input.insert( c ).first ), c );
    std::set<int> test{20, 10, 30};
    auto it = test.begin();
    int i   = 0;
    for ( auto elem : input ) {
        std::cout << elem << std::endl;
        if ( ++i == 4 ) break;
        // ASSERT_EQ( elem, *( it++ ) );
    }
}
