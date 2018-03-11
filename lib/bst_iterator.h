#pragma once

#include<iterator>

namespace tlib {
    /**
     * @brief 
     * 
     * @tparam bst_t_ 
     * @tparam Compare_ 
     */
    template<
        class bst_t_, 
        class pointer_, 
        class reference_
        > 
    class bst_iterator : public std::iterator<
        const std::bidirectional_iterator_tag,
        typename bst_t_::key_type, 
        typename bst_t_::difference_type,
        pointer_,
        reference_
        > {

        public:
            using iterator_category = const std::bidirectional_iterator_tag;
            using value_type = typename bst_t_::value_type;
            using difference_type = typename bst_t_::difference_type;
            using pointer = typename bst_t_::pointer;
            using const_pointer = typename bst_t_::const_pointer;
            using reference = typename bst_t_::reference;
            using const_reference = typename bst_t_::const_reference;
            
            bool operator== (const bst_iterator& rhs) const;

            bool operator!= (const bst_iterator& rhs) const;

            const_reference operator* () const {
                return (*pointee_).key_;
            }

            bst_iterator& operator++ ();

            bst_iterator operator++ (int);

            bst_iterator operator-- ();

            bst_iterator operator-- (int);

        private:
            using key_type = typename bst_t_::key_type;
            using allocator_type = typename bst_t_::allocator_type;
            using node = bst_node<key_type>*;
            using key_compare = typename bst_t_::key_compare;
            using value_compare = typename bst_t_::value_compare;
            using link_type = tlib::bst_node<key_type, key_compare, allocator_type>*;
            
            friend class tlib::bst<key_type, key_compare, allocator_type>;

            link_type pointee_;

            /**
             * @brief Construct a new bst iterator object
             * 
             */
            explicit bst_iterator(const link_type& pointee): pointee_(pointee) {}

        };
}