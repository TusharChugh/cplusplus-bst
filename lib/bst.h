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
    /**
     * @brief Returns an iterator to the first element(smallest value)
     *
     * @return iterator iterator to the first element
     */
    iterator begin() noexcept {
        return make_iterator( header_->left_ );
    }

    /**
     * @brief Returns an constant iterator to the first element(smallest value)
     *
     * @return const_iterator constant iterator to the first element
     */
    const_iterator begin() const noexcept {
        return make_iterator( static_cast<const_node_pointer_>( header_->left_ ) );
    }

    const_iterator cbegin() const noexcept {
        return make_iterator( static_cast<const_node_pointer_>( header_->left_ ) );
    }

    /**
     * @brief Returns an iterator to the end element. End is after the last element
     *
     * @return iterator iterator to the end element
     */
    iterator end() noexcept {
        return make_iterator( header_ );
    }

    /**
     * @brief Returns an constant iterator to the end element. End is after the last element
     *
     * @return const_iterator constant iterator to the end element
     */
    const_iterator end() const noexcept {
        return make_iterator( static_cast<const_node_pointer_>( header_ ) );
    }

    /**
     * @brief Returns an constant iterator to the end element. End is after the last element
     *
     * @return const_iterator constant iterator to the end element
     */
    const_iterator cend() const noexcept {
        return make_iterator( static_cast<const_node_pointer_>( header_ ) );
    }

    // Capacity
    /**
     * @brief checks whether the container is empty
     *
     * @return true if container is empty
     * @return false if container is not empty
     */
    inline bool empty() const noexcept {
        return size_ == 0;
    }

    /**
     * @brief returns the number of elements
     *
     * @return size_t number of elements
     */
    inline size_t size() const noexcept {
        return size_;
    }

    // Modifiers
    // Insert elements. lvalue reference (copy lvalues)
    /**
     * @brief Insert elements
     *
     * @param value value to be inserted
     * @return std::pair<iterator, bool> iterator to the inserted element, true if unique element
     */
    std::pair<iterator, bool> insert( const value_type& value ) {
        return insert_unique( value );
    }

    // Modifiers
    // Insert elements.Rvalue reference. no type deduction
    // Not a universal reference
    // move rvalues
    // emplace backs has type deduction for args
    // value is an lvalue as it has a name
    // type of value is rvalue reference to value_type(T)
    // this is why we need to turn it back to rvalue
    // need to call std::move in all the functions where this value is cascaded to preserve the
    // rvalueness
    /**
     * @brief Insert elements
     *
     * @param value value to be inserted
     * @return std::pair<iterator, bool> iterator to the inserted element, true if unique element
     */
    std::pair<iterator, bool> insert( value_type&& value ) {
        // std::cout << "rvalue insert " << std::endl;
        return insert_unique( std::move( value ) );
    }

    /**
     * @brief clears the contents
     *
     */
    void clear() noexcept;

    // erase elements
    /**
     * @brief erases element at the given position
     *
     * @param pos iterator to the given position
     * @return iterator
     */
    iterator erase( const_iterator pos );

    /**
     * @brief erarses element in the range of positions
     *
     * @param first iterator to the first elment
     * @param last iterator to the last element
     * @return iterator iterator to the replaced element for the first
     */
    iterator erase( const_iterator first, const_iterator last );

    size_type erase( const key_type& key );

    // Lookup
    /**
     * @brief Find the given key
     *
     * @param x key to be find
     * @return iterator itertor to the found key
     */
    iterator find( key_type const& x ) const;

    // Observers
    /**
     * @brief returns the function that compares keys
     *
     * @return key_compare function that compares keys
     */
    key_compare key_comp() const {
        return compare_;
    }

    /**
     * @brief returns the function that compares keys in objects of type value_type;
     *
     * @return key_compare
     */
    key_compare value_comp() const {
        return compare_;
    }

    /**
     * @brief Get the associated allocator
     *
     * @return node_allocator_& allocator
     */
    node_allocator_& get_allocator() noexcept {
        return nat_;
    }

    // Constructors
    /**
     * @brief Construct a new bst object
     *  Default constructor
     */
    explicit bst( const Compare_& comp = Compare_(), const Allocator_& alloc = Allocator_() )
        : compare_( comp ), nat_( node_allocator_( alloc ) ), size_( 0 ),
          header_( make_node_holder( value_type{} ).release() ) {
        this->header_->left_  = this->header_;
        this->header_->right_ = this->header_;
    };

    // Destructors
    ~bst() = default;

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

    node_holder_ make_node_holder( const value_type& value ) {
        node_allocator_& na_ = get_allocator();
        node_holder_ nh_( na_.allocate( 1 ), node_destructor_( na_ ) );
        node_traits_::construct( na_, nh_.get(), value );
        nh_.get_deleter().value_constructed_ = true;
        return std::move( nh_ );
    }

    node_holder_ make_node_holder( value_type&& value ) {
        // std::cout << "args holders " << std::endl;
        node_allocator_& na_ = get_allocator();
        node_holder_ nh_( na_.allocate( 1 ), node_destructor_( na_ ) );
        node_traits_::construct( na_, nh_.get(), std::forward<value_type>( value ) );
        nh_.get_deleter().value_constructed_ = true;
        return std::move( nh_ );
    }

    // Modifiers
    // Insert elements. Make this as const iterator??
    std::pair<iterator, bool> insert_unique( const value_type& value ) {
        node_holder_ h_             = make_node_holder( std::move( value ) );
        node_pointer_ root_         = ( *header_ ).parent_;
        node_pointer_ inserted_node = h_.release();

        if ( root_ == nullptr ) {
            ( *header_ ).parent_   = inserted_node;
            ( *header_ ).left_     = inserted_node;
            ( *header_ ).right_    = inserted_node;
            inserted_node->parent_ = header_;
            size_++;
            return std::make_pair( make_iterator( inserted_node ), true );
        }

        node_pointer_ parent = root_;
        node_pointer_ x      = root_;

        while ( x != nullptr ) {
            parent = x;
            if ( compare_( inserted_node->key_, x->key_ ) )
                x = x->left_;
            else if ( compare_( x->key_, inserted_node->key_ ) )
                x = x->right_;
            else
                return std::make_pair( make_iterator( x ), false );
        }

        if ( compare_( inserted_node->key_, parent->key_ ) ) {
            parent->left_ = inserted_node;
        } else
            parent->right_ = inserted_node;
        inserted_node->parent_ = parent;
        // Update leftmost and right most
        if ( compare_( inserted_node->key_, leftmost()->key_ ) ) ( *header_ ).left_ = inserted_node;
        if ( !( compare_( inserted_node->key_, rightmost()->key_ ) ) &&
             !( compare_( rightmost()->key_, inserted_node->key_ ) ) ) {
            ( *header_ ).right_   = inserted_node;
            inserted_node->right_ = header_;
        }

        size_++;
        return std::make_pair( make_iterator( inserted_node ), true );
    }

    template<typename Vp_> std::pair<iterator, bool> insert_unique( Vp_&& value ) {
        node_holder_ h_             = make_node_holder( std::move( value ) );
        node_pointer_ root_         = ( *header_ ).parent_;
        node_pointer_ inserted_node = h_.release();

        if ( root_ == nullptr ) {
            ( *header_ ).parent_   = inserted_node;
            ( *header_ ).left_     = inserted_node;
            ( *header_ ).right_    = inserted_node;
            inserted_node->parent_ = header_;
            size_++;
            return std::make_pair( make_iterator( inserted_node ), true );
        }

        node_pointer_ parent = root_;
        node_pointer_ x      = root_;

        while ( x != nullptr ) {
            parent = x;
            if ( compare_( inserted_node->key_, x->key_ ) )
                x = x->left_;
            else if ( compare_( x->key_, inserted_node->key_ ) )
                x = x->right_;
            else
                return std::make_pair( make_iterator( x ), false );
        }

        if ( compare_( inserted_node->key_, parent->key_ ) )
            parent->left_ = inserted_node;

        else
            parent->right_ = inserted_node;
        inserted_node->parent_ = parent;
        // Update leftmost and right most
        if ( compare_( inserted_node->key_, leftmost()->key_ ) ) ( *header_ ).left_ = inserted_node;
        if ( !( compare_( inserted_node->key_, rightmost()->key_ ) ) &&
             !( compare_( rightmost()->key_, inserted_node->key_ ) ) ) {
            ( *header_ ).right_   = inserted_node;
            inserted_node->right_ = header_;
        }

        size_++;
        return std::make_pair( make_iterator( inserted_node ), true );
    }

    node_pointer_& root() {
        return this->header_->parent_;
    }

    const_node_pointer_& root() const {
        return static_cast<const_node_pointer_>( this->header_->parent_ );
    }

    node_pointer_& leftmost() noexcept {
        return this->header_->left_;
    }

    const_node_pointer_ leftmost() const noexcept {
        return this->header_->left_;
    }

    node_pointer_& rightmost() noexcept {
        return this->header_->right_;
    }

    const_node_pointer_ rightmost() const noexcept {
        return this->header_->right_;
    }
}; // class bst
} // namespace tlib
