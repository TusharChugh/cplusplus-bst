#pragma once

#include "config.h"

#include "bst_node.h"

#include "bst_iterator.h"

namespace tlib {

// forward declare bst class and bst iterator class
template<class Key_, class Compare_, class Allocator_> class bst;

template<class bst_node_t_> class bst_iterator;

/**
 * @brief Implementation of binary search tree which mimics std::set implementation of STL
 *
 * @tparam __Key The key to be stored
 * @tparam std::less<__Key> Comparator associated with the type Key
 * @tparam std::allocator<__Key> Allocator to store the keys in the bst
 */
template<class Key_, class Compare_ = std::less<Key_>, class Allocator_ = std::allocator<Key_>>
class bst {
private:
    using alloc_traits_ = typename std::allocator_traits<Allocator_>;

public:
    using key_type        = Key_;
    using value_type      = Key_;
    using size_type       = typename alloc_traits_::size_type;
    using difference_type = typename alloc_traits_::difference_type;
    using key_compare     = Compare_;
    using value_compare   = Compare_;
    using allocator_type  = Allocator_;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename alloc_traits_::pointer;
    using const_pointer   = typename alloc_traits_::const_pointer;

private:
    using node_               = bst_node<Key_, typename alloc_traits_::void_pointer>;
    using const_node_         = const bst_node<Key_, typename alloc_traits_::void_pointer>;
    using node_allocator_     = typename alloc_traits_::template rebind_alloc<node_>;
    using node_traits_        = std::allocator_traits<node_allocator_>;
    using node_pointer_       = typename node_traits_::pointer;
    using const_node_pointer_ = typename node_traits_::const_pointer;

public:
    using iterator         = tlib::bst_iterator<node_>;
    using const_iterator   = tlib::bst_iterator<const_node_>;
    using node_destructor_ = bst_node_destructor<node_allocator_>;
    using node_holder_     = std::unique_ptr<node_, node_destructor_>;

    // Iterators
    // Begin
    iterator begin() noexcept {
        // std::cout << "called begin " << ( *header_ ).left_->key_ << std::endl;
        // return make_iterator( ( *header_ ).left_ );
    }

    const_iterator begin() const noexcept {
        // return make_iterator( leftmost() );
    }
    const_iterator cbegin() const noexcept {
        // return make_iterator( leftmost() );
    }

    // End
    iterator end() noexcept {
        // return make_iterator( header_ );
    }
    const_iterator end() const noexcept {
        // return make_iterator( rightmost() );
    }
    const_iterator cend() const noexcept {
        // return make_iterator( rightmost() );
    }

    // Capacity
    inline bool empty() const noexcept {
        return size_ == 0;
    }
    inline size_t size() const noexcept {
        return size_;
    }

    // Modifiers
    // Insert elements. Make this as const iterator??
    std::pair<iterator, bool> insert( const value_type& value ) {
        return insert_unique( value );
    }

    // Modifiers
    // Insert elements. Make this as const iterator??
    std::pair<iterator, bool> insert( value_type&& value ) {
        std::cout << "Am I called?? ";
        return insert_unique( std::move( value ) );
    }

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

    node_allocator_& get_allocator() noexcept {
        return nat_;
    }

    // allocator_type get_allocator() const {
    //     return *static_cast<const Node_Allocator_*>( &this );
    // }

    // Constructors
    /**
     * @brief Construct a new bst object
     *  Default constructor
     */
    explicit bst( const Compare_& comp = Compare_(), const Allocator_& alloc = Allocator_() )
        : compare_( comp ), nat_( node_allocator_( alloc ) ), header_( make_node( value_type{} ) ),
          size_( 0 ) {
        this->header_->left_  = this->header_;
        this->header_->right_ = this->header_;
    };

    // // Destructors
    // ~bst() {
    //     // node_pointer_ left = root_left;
    //     // node_pointer_ left = root_right;
    //     // while(root) {
    //     //     delete root;
    //     // }
    //     // TODO
    //     // Can't use the default constructor. Need to delete the pointers recursively
    // }

private:
    const key_compare compare_;
    node_allocator_ nat_;
    size_t size_;
    node_pointer_ header_;

    static constexpr size_t ONE_NODE = 1;

    iterator make_iterator( node_pointer_& node ) noexcept {
        return iterator( node );
    }

    const_iterator make_iterator( const node_pointer_& node ) const noexcept {
        return const_iterator( node );
    }

    void delete_node( node_pointer_ node ) {
        // node_allocator_.deallocate( node, ONE_NODE );
    }

    // Node_Holder_ make_node_holder() {
    //     Node_Allocator_& na_ = get_allocator();
    //     Node_Holder_ nh_(Node_Allocator_::allocator_traits::allocate(na_, 1), na_);
    //     return nh_;
    // }

    node_pointer_ make_node( const_reference key ) {
        node_allocator_& na_ = get_allocator();
        node_pointer_ np_    = na_.allocate( 1 );
        na_.construct( np_, key );
        return np_;
    }

    node_holder_ make_node_holder( const_reference key ) {
        node_allocator_& na_ = get_allocator();
        node_pointer_ np_    = na_.allocate( 1 );
        na_.construct( np_, key );
        node_holder_ nh_( np_, node_destructor_( na_ ) );
        nh_.get_deleter().value_constructed_ = true;
        return std::move( nh_ );
    }

    // Modifiers
    // Insert elements. Make this as const iterator??
    std::pair<iterator, bool> insert_unique( const value_type& value ) {
        node_pointer_ root_         = ( *header_ ).parent_;
        node_holder_ h_             = make_node_holder( value );
        node_pointer_ inserted_node = h_.release();

        if ( root_ == nullptr ) {
            ( *header_ ).parent_ = inserted_node;
            ( *header_ ).left_   = inserted_node;
            ( *header_ ).right_  = inserted_node;
            // inserted_node->parent_ = header_;
            size_++;
            return std::make_pair( make_iterator( inserted_node ), true );
        }

        node_pointer_ parent = root_;
        node_pointer_ x      = root_;

        while ( x != nullptr ) {
            parent = static_cast<node_pointer_>( x );
            if ( compare_( value, x->key_ ) )
                x = static_cast<node_pointer_>( x->left_ );
            else if ( compare_( x->key_, value ) )
                x = static_cast<node_pointer_>( x->right_ );
            else
                return std::make_pair( make_iterator( x ), false );
        }

        if ( compare_( value, parent->key_ ) ) {
            parent->left_ = inserted_node;
        } else
            parent->right_ = inserted_node;
        size_++;
        return std::make_pair( make_iterator( inserted_node ), true );
    }

    template<typename Vp_> std::pair<iterator, bool> insert_unique( Vp_&& value ) {
        node_holder_ h_ = make_node_holder( std::forward<Vp_>( value ) );
        std::cout << "serious";
        node_pointer_ root_         = ( *header_ ).parent_;
        node_pointer_ inserted_node = h_.release();

        if ( root_ == nullptr ) {
            ( *header_ ).parent_ = inserted_node;
            ( *header_ ).left_   = inserted_node;
            ( *header_ ).right_  = inserted_node;
            // inserted_node->parent_ = header_;
            size_++;
            return std::make_pair( make_iterator( inserted_node ), true );
        }

        node_pointer_ parent = root_;
        node_pointer_ x      = root_;

        while ( x != nullptr ) {
            parent = static_cast<node_pointer_>( x );
            if ( compare_( value, x->key_ ) )
                x = static_cast<node_pointer_>( x->left_ );
            else if ( compare_( x->key_, value ) )
                x = static_cast<node_pointer_>( x->right_ );
            else
                return std::make_pair( make_iterator( x ), false );
        }

        if ( compare_( value, parent->key_ ) ) {
            parent->left_ = inserted_node;
        } else
            parent->right_ = inserted_node;
        size_++;
        return std::make_pair( make_iterator( inserted_node ), true );
    }

    node_pointer_& root() {
        return this->header_->parent_;
    }

    const_node_pointer_& root() const {
        return this->header_->parent_;
    }

    node_pointer_ leftmost() {
        return this->header_->left_;
    }

    const_node_pointer_ leftmost() const {
        return this->header_->left_;
    }

    node_pointer_ rightmost() {
        return this->header_->right_;
    }

    const_node_pointer_ rightmost() const {
        return this->header_->right_;
    }
}; // class bst
} // namespace tlib
