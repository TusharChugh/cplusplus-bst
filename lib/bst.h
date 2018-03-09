#pragma once

#include <memory>
#include <functional>

namespace tlib {
    /**
     * @brief Implementation of binary search tree which mimics std::set implementation of STL
     * 
     * @tparam __Key The key to be stored 
     * @tparam std::less<__Key> Comparator associated with the type Key
     * @tparam std::allocator<__Key> Allocator to store the keys in the bst
     */
    template <
        typename __Key, 
        typename __Compare = std::less<__Key>,
        typename __Allocator = std::allocator<__Key>
    > class bst {
        
        public:
            using key_type = __Key;
            using value_type = __Key;
            using size_type = typename __Allocator::size_type;
            using difference_type = typename __Allocator::difference_type;
            using key_compare = __Compare;
            using value_compare = __Compare;
            using allocator_type = __Allocator;        
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = typename std::allocator_traits<__Allocator>::pointer;
            using const_pointer = typename std::allocator_traits<__Allocator>::const_pointer;
            //using iterator = tlib::forward_tlist_iterator<list_type, pointer, reference >;
            //using const_iterator = tlib::forward_tlist_iterator<list_type, const_pointer, const_reference>;
    
            //Insert elements
            //std::pair<iterator, bool> insert(const value_type&);
            //std::pair<iterator, bool> insert(value_type&);

            //Find key
           // iterator find(key_type const & x) const;

            //Constructors

        private:
        struct BSTNode;
        using node = typename std::shared_ptr<BSTNode>;
        struct BSTNode {
            key_type key_;
            node left_;
            node right_;
            node parent_;
            BSTNode(const_reference key) : key_(key), left_(nullptr), right_(nullptr), parent_(nullptr) {}
        };
        
    };
}

