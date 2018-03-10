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
                        using iterator = tlib::bst_iterator<key_type, key_compare, pointer, reference>;
            using node = bst_node<key_type>*;
    
            //Iterators
            //Begin
            iterator begin() noexcept;
            const_iterator begin() const noexcept;
            const_iterator cbegin() const noexcept;

            //End
            iterator end() noexcept;
            const_iterator end() const noexcept;
            const_iterator cend() const noexcept;

            //Capacity
            bool empty() const noexcept;
            inline size_t size() const noexcept { return size_; };

            //Modifiers
            //Insert elements
            std::pair<iterator, bool> insert(const value_type&);
            std::pair<iterator, bool> insert(value_type&);

            void clear() noexcept;

            //erase elements
            iterator erase(const_iterator pos);
            iterator erase(const_iterator first, const_iterator last);
            size_type erase( const key_type& key );

            //Lookup
            //Find key
            iterator find(key_type const & x) const;

            //Constructors
            /**
             * @brief Construct a new bst object
             *  Default constructor
             */
            explicit bst(const key_compare& comp = key_compare(), 
              const allocator_type& alloc = allocator_type()): 
                compare_(comp), allocator_(alloc), size_(0) {};

        private:

            const key_compare compare_;
            const allocator_type allocator_;
            size_t size_;
            
            node root_;
    };
}

