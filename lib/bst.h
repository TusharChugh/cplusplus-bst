#pragma once

#include "bst_iterator.h"
#include "bst_node.h"

namespace tlib {
/**
 * @brief Implementation of binary search tree which mimics std::set implementation of STL
 *
 * @tparam __Key The key to be stored
 * @tparam std::less<__Key> Comparator associated with the type Key
 * @tparam std::allocator<__Key> Allocator to store the keys in the bst
 */
template<class Key_, class Compare_ = std::less<Key_>, class Allocator_ = std::allocator<Key_>>
class bst {
    using node_type    = bst_node<Key_, Compare_, Allocator_>;
    using node_pointer = bst_node<Key_, Compare_, Allocator_>*;
    using Node_Allocator_ =
        typename Allocator_::template rebind<bst_node<Key_, Compare_, Allocator_>>::other;

public:
    using key_type        = Key_;
    using value_type      = Key_;
    using size_type       = typename Allocator_::size_type;
    using difference_type = typename Allocator_::difference_type;
    using key_compare     = Compare_;
    using value_compare   = Compare_;
    using allocator_type  = Allocator_;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename std::allocator_traits<Allocator_>::pointer;
    using const_pointer   = typename std::allocator_traits<Allocator_>::const_pointer;
    using const_iterator  = tlib::bst_iterator<node_type, const_pointer, const_reference>;
    using iterator        = tlib::bst_iterator<node_type, pointer, reference>;

    // Iterators
    // Begin
    iterator begin() noexcept {
        return make_iterator( root_ );
    }
    const_iterator begin() const noexcept {
        return make_const_iterator( root_ );
    }
    const_iterator cbegin() const noexcept {
        return make_const_iterator( root_ );
    }

    // End
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    // Capacity
    inline bool empty() const noexcept {
        return size_ == 0;
    }
    inline size_t size() const noexcept {
        return size_;
    }

    // Modifiers
    // Insert elements. Make this as const iterator??
    iterator insert( const value_type& value );
    // {
    // if(root_) std::cout<<"Before insertion "<<root_->key_<<std::endl;
    // node_pointer inserted_node = nullptr;
    // bool newly_inserted = true;
    // root_ = insert(root_, value, inserted_node, newly_inserted);
    // if(newly_inserted) size_++;
    // std::cout<<root_<<inserted_node<<std::endl;
    // std::cout<<"After insertion "<<root_->key_<<" "<<inserted_node->key_<<std::endl;
    // return make_iterator(inserted_node);
    // return std::make_pair(make_iterator(inserted_node), newly_inserted);
    // auto start = root_;
    // if ( start == nullptr ) {
    //     std::cout << "Adding node at the end" << std::endl;
    //     return std::make_pair( make_node( key ), true );
    // }

    // size_t size = size_;
    // node_pointer parent;

    // while ( size ) {
    //     int comp = compare_( key, node_key_ );
    //     if ( comp < 0 ) {

    //     } else if ( comp > 0 ) {

    //     } else {
    //         return std::make_pair( node, false );
    //     }
    // }
    // = compare_( key, node->key_ );

    // if ( cmp < 0 ) {
    //     node->left_ = insert( node->left_, key, inserted_node, newly_inserted );
    // } else if ( cmp > 0 ) {
    //     node->right_ = insert( node->right_, key, inserted_node, newly_inserted );
    // } else if ( cmp == 0 ) {
    //     newly_inserted = false;
    //     inserted_node  = node;
    // }
    // return std::make_pair( node, inserted_node );
    // }

    void clear() noexcept;

    // erase elements
    iterator erase( const_iterator pos );
    iterator erase( const_iterator first, const_iterator last );
    size_type erase( const key_type& key );

    // Lookup
    // Find key
    iterator find( key_type const& x ) const;

    // Observers
    key_compare key_comp() const {
        return compare_;
    }
    key_compare value_comp() const {
        return compare_;
    }

    allocator_type get_allocator() const {
        return *static_cast<const Node_Allocator_*>( &this );
    }

    // Constructors
    /**
     * @brief Construct a new bst object
     *  Default constructor
     */
    explicit bst( const Compare_& comp = Compare_(), const Allocator_& alloc = Allocator_() )
        : compare_( comp ), allocator_( alloc ), size_( 0 ), root_( nullptr ){};

    // Destructors
    ~bst() {
        // node_pointer left = root_left;
        // node_pointer left = root_right;
        // while(root) {
        //     delete root;
        // }
        // TODO
        // Can't use the default constructor. Need to delete the pointers recursively
    }

private:
    const key_compare compare_;
    const allocator_type allocator_;
    size_t size_;

    node_pointer root_;
    const node_pointer end_ = nullptr;

    static constexpr size_t ONE_NODE = 1;

    iterator make_iterator( node_pointer& node ) {
        return iterator( node );
    }

    bst::iterator make_iterator( node_pointer& node ) const noexcept {
        return iterator( node );
    }

    bst::const_iterator make_const_iterator( const node_pointer& node ) const noexcept {
        return const_iterator( node );
    }

    void delete_node( node_pointer node ) {
        Node_Allocator_::deallocate( node, 1 );
    }

    node_pointer make_node() {
        return Node_Allocator_::allocate( 1 );
    }
    node_pointer make_node( const_reference key ) {
        node_pointer temp_ = make_node();
        try {
            get_allocator().construct( temp_, key );
        } catch ( ... ) {
            delete_node( temp_ );
            // TODO: Through exception
        }
        return new node_type( key );
    }

    node_pointer make_node( const_reference key, node_pointer left, node_pointer right,
                            node_pointer parent ) {
        node_pointer temp_ = make_node();
        try {
            get_allocator().construct( temp_, key, left, right, parent );
        } catch ( ... ) {
            delete_node( temp_ );
            // TODO: Through exception
        }
        return new node_type( key );
    }

    // std::tuple<node_pointer, bool> insert(
    //     node_pointer& node, const_reference key) {
    //     auto start = node;
    //     if(start == nullptr) {
    //         std::cout<<"Adding node at the end"<<std::endl;
    //         return std::make_pair(make_node(key), true);
    //     }

    //     size_t size = size_;
    //     node_pointer parent;

    //     while(size) {
    //         int comp = compare_(key, node_key_);
    //         if(comp < 0) {

    //         }
    //         else if(comp > 0) {

    //         }
    //         else {
    //             return std::make_pair(node, false);
    //         }
    //     }
    //     = compare_(key, node->key_);

    //     if(cmp < 0) {
    //         node->left_ = insert(node->left_, key, inserted_node, newly_inserted);
    //     }
    //     else if(cmp > 0) {
    //         node->right_ = insert(node->right_, key, inserted_node, newly_inserted);
    //     }
    //     else if(cmp == 0) {
    //         newly_inserted = false;
    //         inserted_node = node;
    //     }
    //     return std::make_pair(node, inserted_node);
    // }
};
} // namespace tlib
