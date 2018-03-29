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
    /**
     * @brief Helper function to find if node is the left child of the parent
     *
     * @param x_ input node
     * @return true if the node is left child of the parent
     * @return false if node is not the left child of the parent
     */
    bool is_left_child( node_pointer_ x_ ) noexcept {
        return ( x_ == static_cast<node_pointer_>( x_->parent_->left_ ) );
    }

    /**
     * @brief Given the pointer to the node finds the minimum value of the subtree
     *
     * @param x_ input node pointer
     * @return node_pointer_ pointer to the node with min val
     */
    node_pointer_ tree_min( node_pointer_ x_ ) noexcept {
        while ( x_->left_ != nullptr ) {
            x_ = x_->left_;
        }
        return x_;
    }

    /**
     * @brief Given the pointer to the node finds the maximum value of the subtree
     *
     * @param x_ input node pointer
     * @return node_pointer_ pointer to the node with max val
     */
    node_pointer_ tree_max( node_pointer_ x_ ) noexcept {
        while ( x_->right_ != nullptr ) {
            x_ = x_->right_;
        }
        return x_;
    }

    /**
     * @brief get the next element following the inorder traversal
     *
     * @param x_ pointer to the input node
     * @return node_pointer_ pointer to the next node
     */
    node_pointer_ tree_next( node_pointer_ x_ ) noexcept {
        // Case 1: if there are elements in the right subtree
        // then the successor is the left most element of the right subtree
        if ( x_->right_ != nullptr ) return tree_min( x_->right_ );
        // Case 2: if there is no element in the right  and this node is parent's right child
        while ( !is_left_child( x_ ) )
            x_ = x_->parent_;
        // Case 3: if there is no element in the right  and this node is parent's left child
        return x_->parent_;
    }

public:
    /**
     * @brief Returns the value of the node pointed by the iterator
     *
     * @return const_reference value
     */
    const_reference operator*() const {
        return pointee_->key_;
    }

    /**
     * @brief Returns the next element. Pre increment
     *
     * @return bst_iterator& reference to the next element
     */
    bst_iterator& operator++() {
        pointee_ = tree_next( pointee_ );
        return *this;
    }

    /**
     * @brief Returns the next element. Post increment
     *
     * @return bst_iterator& reference to the next element
     */
    bst_iterator operator++( int ) {
        auto temp_ = *this;
        ++( *this );
        return temp_;
    }

    bst_iterator operator--();

    bst_iterator operator--( int );

    /**
     * @brief Returns if the the two iterators lhs and rhs are equal
     *
     * @param lhs first iterator
     * @param rhs second iterator
     * @return true if lhs is equal to rhs
     * @return false if lhs is not equal to rhs
     */
    friend bool operator==( const bst_iterator& lhs, const bst_iterator& rhs ) {
        return lhs.pointee_ == rhs.pointee_;
    }

    /**
     * @brief Returns if the the two iterators lhs and rhs are not equal
     *
     * @param lhs first iterator
     * @param rhs second iterator
     * @return true if lhs is not equal to rhs
     * @return false if lhs is equal to rhs
     */
    friend bool operator!=( const bst_iterator& lhs, const bst_iterator& rhs ) {
        return !( lhs == rhs );
    }

    /**
     * @brief Construct a new bst iterator object
     * Default constructpr
     */
    bst_iterator();

    /**
     * @brief Destroy the bst iterator object
     * Destructor
     */
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