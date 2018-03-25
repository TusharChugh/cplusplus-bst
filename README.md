# BST implementatiion in C++

## Build and run the code  using bazel
1. Install bazel: https://docs.bazel.build/versions/master/install.html
2. Build the code: bazel build //test:bst-test
3. Run the tests: bazel run //test:bst-test

## More on bazel
1. Configuring google tests: https://docs.bazel.build/versions/master/cpp-use-cases.html

## Tested Environment
1. OS: Ubuntu 14.04
2. GCC version: 6.3.0-18
3. C++ version: > 11

2. More of gtest and bazel: https://docs.bazel.build/versions/master/test-encyclopedia.html

## C++ reference
1. Code is based on c++ set implementation: http://en.cppreference.com/w/cpp/container/set

## C++ Iterators
1. Use bidiectional iterators
2. Two option to implement ++ operator with iterator (a. use of queue b. use parent pointer). 

 ## ToDo's (not in sequence)
 1. Implement insert
 2. Implement ++ for iterator
 3. Implement begin and end functions
 4. test 1,2 and 3
 5. Implement destructor, copy/move constructor and swap function
 6. Allocator construct has been depricated in c++17. find the alternative
 7. Add google log and debug features
 8. Rebind with node type and remove new

 ## Notes:
 1. C++ set implementation uses red-black trees
 2. https://stackoverflow.com/questions/2762568/c-c-include-file-order-best-practices

 missing PIMPL idiom

 ## References
1. Apache implementation of red black tree: https://github.com/apache/stdcxx/blob/trunk/include/rw/_tree.h
2. GCC implementation: https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.1/stl__tree_8h-source.html
3. LLVM: https://github.com/google/libcxx/blob/27c836ff3a9c505deb9fd1616012924de8ff9279/include/__tree



## Design choices
1. BST declaration 
Option 1:   
template<class Key_, class Compare_ = std::less<Key_>, class Allocator_ = std::allocator<Key_>> 
In this case we'll need to declare pointer to node like :
using node_pointer    = bst_node<key_type, key_compare, allocator_type>*;

But we don't need compare type here

2. Option 2:  
template<class Key_, class VoidPtr_>
and then rebind void pointer to the node pointer  