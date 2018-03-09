#pragma once

#include "bst_node.h"
#include "bst_iterator.h"

namespace tlib {
    /**
     * @brief Implementation of binary search tree which mimics std::set implementation of STL
     * 
     * @tparam __Key The key to be stored 
     * @tparam std::less<__Key> Comparator associated with the type Key
     * @tparam std::allocator<__Key> Allocator to store the keys in the bst
     */
    template <
    class Key_, 
    class Compare_ = std::less<Key_>,
    class Allocator_ = std::allocator<Key_>
    > class bst {
        struct BSTNode;
        public:
            using key_type = Key_;
            using value_type = Key_;
            using size_type = typename Allocator_::size_type;
            using difference_type = typename Allocator_::difference_type;
            using key_compare = Compare_;
            using value_compare = Compare_;
            using allocator_type = Allocator_;        
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = typename std::allocator_traits<Allocator_>::pointer;
            using const_pointer = typename std::allocator_traits<Allocator_>::const_pointer;
            using const_iterator = tlib::bst_iterator<key_type, key_compare, const_pointer, const_reference>;
            //using const_iterator = tlib::forward_tlist_iterator<list_type, const_pointer, const_reference>;
    
            //Insert elements
            //std::pair<iterator, bool> insert(const value_type&);
            //std::pair<iterator, bool> insert(value_type&);

            //Find key
           // iterator find(key_type const & x) const;

            //Constructors
            /**
             * @brief Construct a new bst object
             *  Default constructor
             */
            bst();

            size_t size() const;

        private:
            using iterator = tlib::bst_iterator<key_type, key_compare, pointer, reference>;
            using node = bst_node<key_type>*;
            
            node root;
            size_t size_ = 0;
    };
}

