#pragma once

#include <functional>
#include <memory>

namespace tlib {

template<class Allocator_> class bst_node_destructor {
    using allocator_type    = Allocator_;
    using allocator_traits_ = std::allocator_traits<allocator_type>;
    using value_type        = typename allocator_traits_::value_type;

public:
    using pointer = typename std::allocator_traits<Allocator_>::pointer;

private:
    allocator_type& node_allocator_;

    bst_node_destructor& operator=( const bst_node_destructor& );

public:
    bool value_constructed_;

    /**
     * @brief constructor for the bode destructor
     *
     * @param node_allocator node allocator rebinded from type Key
     */
    LIBCPP_INLINE_VISIBILITY_
    explicit bst_node_destructor( allocator_type& node_allocator ) noexcept
        : node_allocator_( node_allocator ), value_constructed_( false ) {}

    /**
     * @brief operator to be called for destroying/deallocating the node
     *
     * @param p_ pointer to the node
     */
    LIBCPP_INLINE_VISIBILITY_
    void operator()( pointer p_ ) noexcept {
        if ( value_constructed_ )
            allocator_traits_::destroy( node_allocator_, std::addressof( p_->key_ ) );
        if ( p_ ) {
            allocator_traits_::deallocate( node_allocator_, p_, 1 );
            std::cout << "deallocating node pointer" << std::endl;
        }
    }
};

/**
 * @brief Node for Binary Search Tree
 *
 * @tparam Key_
 */
template<class Key_, class VoidPointer_> class bst_node {
public:
    // Define typenames
    using key_type        = Key_;
    using value_type      = Key_;
    using const_reference = const value_type&;
    using pointer_traits =
        typename std::pointer_traits<VoidPointer_>::template rebind<bst_node<Key_, VoidPointer_>>;
    using pointer = typename std::pointer_traits<VoidPointer_>::template rebind<bst_node>;
    using const_pointer =
        typename std::pointer_traits<VoidPointer_>::template rebind<const bst_node>;

    /**
     * @brief Construct a new bst node object
     *
     * @param key key of the node
     * @param left pointer to the left of node
     * @param right pointer to the right of the node
     * @param parent pointer to the parent of the node
     */
    LIBCPP_INLINE_VISIBILITY_
    explicit bst_node( const_reference key, pointer left = nullptr, pointer right = nullptr,
                       pointer parent = nullptr )
        : key_( key ), left_( left ), right_( right ), parent_( parent ) {}

    // Node defination
    const_reference key_;
    pointer left_{nullptr};
    pointer right_{nullptr};
    pointer parent_{nullptr};
};
} // namespace tlib