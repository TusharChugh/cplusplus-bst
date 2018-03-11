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
            using bst_type = bst<key_type, key_compare, allocator_type>;
            using const_iterator = tlib::bst_iterator<bst_type, const_pointer, const_reference>;
            using iterator = tlib::bst_iterator<bst_type, pointer, reference>;
            using node_pointer = bst_node<key_type, key_compare, allocator_type>*;
            using node_type = bst_node<key_type, key_compare, allocator_type>;
    
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
            inline bool empty() const noexcept { return size_ == 0; }
            inline size_t size() const noexcept { return size_; }

            //Modifiers
            //Insert elements
            std::pair<iterator, bool> insert(const value_type& value) {
                if(root_) std::cout<<"Before insertion "<<root_->key_<<std::endl;
                node_pointer inserted_node = nullptr;
                std::pair<node_pointer, bool> result = insert(root_, value, inserted_node);
                if(result.second) size_++;
                root_ = result.first;
                std::cout<<"After insertion "<<root_->key_<<" "<<inserted_node->key_<<std::endl;
                return std::make_pair(make_iterator(inserted_node), result.second);
            }

            void clear() noexcept;

            //erase elements
            iterator erase(const_iterator pos);
            iterator erase(const_iterator first, const_iterator last);
            size_type erase(const key_type& key);

            //Lookup
            //Find key
            iterator find(key_type const & x) const;

            //Observers
            key_compare key_comp() const { return compare_; }
            key_compare value_comp() const { return compare_; }

            //Constructors
            /**
             * @brief Construct a new bst object
             *  Default constructor
             */
            explicit bst(const Compare_& comp = Compare_(), 
              const Allocator_& alloc = Allocator_()): 
                compare_(comp), allocator_(alloc), size_(0), 
                root_(nullptr) {};

            //Destructors
            ~bst() {
                //TODO
                //Can't use the default constructor. Need to delete the pointers recursively
            }

        private:

            const key_compare compare_;
            const allocator_type allocator_;
            size_t size_;
            
            node_pointer root_;
            static constexpr size_t ONE_NODE = 1;

            iterator make_iterator(node_pointer &node) {
                return iterator(node);
            }

            bst::const_iterator make_iterator(const node_pointer &node) const noexcept {
                return const_iterator(node);
            }

            node_pointer make_node(const_reference key) {
                return new node_type(key);
            }

            node_pointer make_node(const_reference key, 
                                    node_pointer left, 
                                    node_pointer right, 
                                    node_pointer parent) {
                return new node_type(key, left, right, parent);
            }
            
            std::pair<node_pointer, bool> insert(
                node_pointer node, const_reference key, node_pointer& inserted_node) {
                if(node == nullptr) {
                    std::cout<<"Adding node at the end"<<std::endl;
                    inserted_node = make_node(key);
                    return std::make_pair(inserted_node, true);
                }

                int cmp = compare_(key, node->key_);
                bool inserted = true;
                if(cmp < 0) {
                    auto left_info = insert(node->left_, key, inserted_node);
                    node->left_ = left_info.first; 
                } 
                else if(cmp > 0) {
                    auto right_info = insert(node->right_, key, inserted_node);
                    node->right_ = right_info.first; 
                }
                else if(cmp == 0) {
                    node_pointer temp = node;
                    node = make_node(key, node->left_, node->right_, node->parent_);
                    delete temp;
                    inserted = true;
                    inserted_node = node;
                }
                return std::make_pair(node, inserted);
            }

    };
}

