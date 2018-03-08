#pragma once

#include <memory>
#include <functional>

namespace tlib {
    template <
        typename __Key, 
        typename __Compare = std::less<__Key>,
        typename __Allocator = std::allocator<__Key>
    > class bst {

    };
}

