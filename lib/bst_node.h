#pragma once

#include <memory>
#include <functional>

namespace tlib {

    //forward declare bst class and bst iterator class
    template <
    class Key_, 
    class Compare_,
    class Allocator_
    > class bst;
    
    template<
    class Key_, 
    class Compare_, 
    class pointer_,
    class reference_
    > class bst_iterator;
    
    /**
     * @brief Node for Binary Search Tree
     * 
     * @tparam Key_ 
     */
    template <
        class Key_, 
        class Compare_ = std::less<Key_>,
        class Allocator_ = std::allocator<Key_>
        >
    class bst_node {
        private:
            //Define typenames
            using key_type = Key_;
            using value_type = Key_;
            using key_compare = Compare_;
            using allocator_type = Allocator_;  
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = typename std::allocator_traits<Allocator_>::pointer;
            using const_pointer = typename std::allocator_traits<Allocator_>::const_pointer;  
            using node = bst_node<key_type>*;
            
            /**
             * @brief Construct a new bst node object
             * 
             * @param key key of the node
             * @param left pointer to the left of node
             * @param right pointer to the right of the node
             * @param parent pointer to the parent of the node
             */
            bst_node(const_reference key, node left, node right, node parent) : 
                key_(key), left_(left = nullptr), 
                right_(right = nullptr), parent_(parent = nullptr) {};

            //bst 
            friend class bst<key_type, key_compare, allocator_type>;

            //bst_iterator class need to access the private of the nodes
            friend class bst_iterator<key_type, key_compare, pointer, reference>;

            friend class bst_iterator<key_type, key_compare, const_pointer, const_reference>;

            /**
             * @brief Destroy the bst node object
             * Default constructor
             */
            ~bst_node() = default;

            //Node defination
            const key_type key_;
            node left_;
            node right_;
            node parent_;
    };
}