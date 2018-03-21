#pragma once

#include <functional>
#include <memory>

namespace tlib {

// forward declare bst class and bst iterator class
template<class Key_, class Compare_, class Allocator_> class bst;

template<class bst_node_t_> class bst_iterator;

/**
 * @brief Node for Binary Search Tree
 *
 * @tparam Key_
 */
template<class Key_, class Compare_ = std::less<Key_>, class Allocator_ = std::allocator<Key_>>
class bst_node {
public:
    // Define typenames
    using key_type        = Key_;
    using value_type      = Key_;
    using key_compare     = Compare_;
    using allocator_type  = Allocator_;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename std::allocator_traits<Allocator_>::pointer;
    using const_pointer   = typename std::allocator_traits<Allocator_>::const_pointer;
    using node_type       = bst_node<key_type, key_compare, allocator_type>;
    using const_node_type = const bst_node<key_type, key_compare, allocator_type>;
    using node_pointer    = bst_node<key_type, key_compare, allocator_type>*;
    using difference_type = typename Allocator_::difference_type;
    /**
     * @brief Construct a new bst node object
     *
     * @param key key of the node
     * @param left pointer to the left of node
     * @param right pointer to the right of the node
     * @param parent pointer to the parent of the node
     */
    explicit bst_node( const_reference key, node_pointer left = nullptr,
                       node_pointer right = nullptr, node_pointer parent = nullptr )
        : key_( key ), left_( left ), right_( right ), parent_( parent ){};

    // bst
    friend class bst<value_type, key_compare, allocator_type>;

    // bst_iterator class need to access the private of the nodes
    friend class bst_iterator<node_type>;

    friend class bst_iterator<const_node_type>;

    /**
     * @brief Destroy the bst node object
     * Default constructor
     */
    ~bst_node() = default;

    // Node defination
    const_reference key_;
    node_pointer left_;
    node_pointer right_;
    node_pointer parent_;
};
} // namespace tlib