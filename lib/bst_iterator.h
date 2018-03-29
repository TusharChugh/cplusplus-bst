#pragma once

#include <iterator>

namespace tlib {
/**
 * @brief
 *
 * @tparam bst_node_t_
 * @tparam Compare_
 */
template<class bst_node_t_>
class bst_iterator
    : public std::iterator<const std::bidirectional_iterator_tag, typename bst_node_t_::pointer> {
    using key_type      = typename bst_node_t_::key_type;
    using node_pointer_ = typename bst_node_t_::pointer;

    template<class, class, class> friend class bst;

public:
    using iterator_category = const std::bidirectional_iterator_tag;
    using value_type        = typename bst_node_t_::value_type;
    using const_reference   = typename bst_node_t_::const_reference;

private:
    bool is_left_child( node_pointer_ x_ ) noexcept {
        return ( x_ == static_cast<node_pointer_>( x_->parent_->left_ ) );
    }

    node_pointer_ tree_min( node_pointer_ x_ ) noexcept {
        while ( x_->left_ != nullptr ) {
            x_ = x_->left_;
        }
        return x_;
    }

    node_pointer_ tree_max( node_pointer_ x_ ) noexcept {
        while ( x_->right_ != nullptr ) {
            x_ = x_->right_;
        }
        return x_;
    }

    node_pointer_ tree_next( node_pointer_ x_ ) noexcept {
        // Case: if there are elements in the right of the node
        // then the successor is the left most element of the right subtree
        if ( x_->right_ != nullptr ) return tree_min( x_->right_ );
        while ( !is_left_child( x_ ) )
            x_ = x_->parent_;
        return x_->parent_;
    }

public:
    const_reference operator*() const {
        return pointee_->key_;
    }

    // pointer operator->() const {
    //     return &( pointee_->key_ );
    // }

    bst_iterator& operator++() {
        pointee_ = tree_next( pointee_ );
        return *this;
    }

    bst_iterator operator++( int ) {
        auto temp_ = *this;
        ++( *this );
        return temp_;
    }

    bst_iterator operator--();

    bst_iterator operator--( int );

    friend bool operator==( const bst_iterator& lhs, const bst_iterator& rhs ) {
        return lhs.pointee_ == rhs.pointee_;
    }

    friend bool operator!=( const bst_iterator& lhs, const bst_iterator& rhs ) {
        return !( lhs == rhs );
    }

    bst_iterator();
    ~bst_iterator() = default;

private:
    node_pointer_ pointee_;

    /**
     * @brief Construct a new bst iterator object
     *
     */
    explicit bst_iterator( const node_pointer_& pointee ) : pointee_( pointee ) {}
};
} // namespace tlib