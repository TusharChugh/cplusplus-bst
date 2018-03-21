#pragma once

#include <iterator>

namespace tlib {
// forward declare bst class and bst iterator class
template<class Key_, class Compare_, class Allocator_> class bst;
/**
 * @brief
 *
 * @tparam bst_node_t_
 * @tparam Compare_
 */
template<class bst_node_t_>
class bst_iterator
    : public std::iterator<const std::bidirectional_iterator_tag, typename bst_node_t_::key_type> {
    using key_type       = typename bst_node_t_::key_type;
    using allocator_type = typename bst_node_t_::allocator_type;
    using key_compare    = typename bst_node_t_::key_compare;
    using value_compare  = typename bst_node_t_::key_compare;
    using node_type      = typename bst_node_t_::node_type;
    using node_pointer   = typename bst_node_t_::node_pointer;

    friend class tlib::bst<key_type, key_compare, allocator_type>;

public:
    using iterator_category = const std::bidirectional_iterator_tag;
    using value_type        = typename bst_node_t_::value_type;
    using pointer           = typename bst_node_t_::pointer;
    using const_pointer     = typename bst_node_t_::const_pointer;
    using reference         = typename bst_node_t_::reference;
    using const_reference   = typename bst_node_t_::const_reference;

    bool operator==( const bst_iterator& rhs ) const;

    bool operator!=( const bst_iterator& rhs ) const;

    const_reference operator*() const {
        std::cout << "Iterator here " << pointee_->key_ << std::endl;
        return ( *pointee_ ).key_;
    }

    bst_iterator& operator++() {
        node_pointer parent = pointee_->parent_;
        // Case 1: nullptr
        if ( pointee_ == nullptr ) {
            throw std::overflow_error( "Past the elements" );
        }
        // Case 2: if there are elements in the right of the node
        // then the successor is the left most element of the right subtree
        else if ( pointee_->right_ != nullptr ) {
            pointee_ = pointee_->right_;
            while ( pointee_->left_ != nullptr ) {
                pointee_ = pointee_->left_;
            }
        }
        // Case 3: No elements of the right side
        else {
            while ( parent != nullptr && pointee_ == parent->right_ ) {
                pointee_ = parent;
                parent   = parent->parent_;
            }
        }
        return *this;
    }

    bst_iterator operator++( int );

    bst_iterator operator--();

    bst_iterator operator--( int );

    bst_iterator();
    ~bst_iterator() = default;

private:
    node_pointer pointee_;

    /**
     * @brief Construct a new bst iterator object
     *
     */
    explicit bst_iterator( const node_pointer& pointee ) : pointee_( pointee ) {
        std::cout << "iterator constructor " << pointee_->key_ << std::endl;
    }
};
} // namespace tlib