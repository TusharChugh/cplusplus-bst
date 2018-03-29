# BST implementatiion in C++

## Why
Writing STL containers from scratch is a good way to dig deeper into C++. Refering to the API's, literature and the source code (which are easily accessible), it is helpful to tune out thought process for leaning effective C++. 
BST is not available as the part of STL but std::set is implemented as red-black tree which is very simple. 
Note: This code base is incomplete and at best represents a way to get started with writing the containers. There are known bugs and issue both related to design and visibility which are to be fixed. 
The thought process which led to this design and the learnings from this project are also shared.


## Build and run the code  using bazel
1. [Install bazel] (https://docs.bazel.build/versions/master/install.html)
2. Build the code: bazel build //test:bst-test
3. Run the tests: bazel run //test:bst-test
4. (OPTIONAL READ): Configuring google tests: https://docs.bazel.build/versions/master/cpp-use-cases.html
https://docs.bazel.build/versions/master/test-encyclopedia.html

## Tested Environment
1. OS: Ubuntu 14.04
2. GCC version: 6.3.0-18
3. C++ version: > 11

2. More of gtest and bazel: 

## C++ reference
1. APIS' are based is based on [c++ set implementation](http://en.cppreference.com/w/cpp/container/set)

## Design choices
### 1. BST Node defination
#### Option 1:   
template<class Key_, class Compare_ = std::less<Key_>, class Allocator_ = std::allocator<Key_>> 
In this case we'll need to declare pointer to node like :
using node_pointer    = bst_node<key_type, key_compare, allocator_type>*;

But we don't need compare type here

#### Option 2:  
template<class Key_, class VoidPtr_>

I went ahead with the option 2 way as used in the llvm implementation. C++17 has [node_handle](http://en.cppreference.com/w/cpp/container/node_handle) which is very similar to the Option1 implementation

### 2. C++ Iterators
1. Use bidiectional iterators (for ++ and -- operator)
2. Two option to implement ++ operator with iterator (a. use of queue b. use parent pointer). In this code parent pointer approach has been used as the other takes in extra memory of order O(N) where N are the number of elements

### 3. Rebind:
1. The allocator templete parameter is the allocator for the type Key_ but we need to allocate the node. So, we rebind the allocator the the node.
rebind_alloc<T>	Alloc::rebind<T>::other if present, otherwise Alloc<T, Args> if this Alloc is Alloc<U, Args>
http://en.cppreference.com/w/cpp/memory/allocator_traits

### 4. Passing lvalue vs passing r value
Two seperate functions for inserting lvalue and rvalue are required. 
'''
//for lvaue
std::pair<iterator,bool> insert( const value_type& value );
'''
'''
for rvalue
std::pair<iterator,bool> insert( value_type&& value );
'''
See the comments in the code for more details.
More resources on lvalue and rvalue:
https://channel9.msdn.com/Shows/Going+Deep/Cpp-and-Beyond-2012-Scott-Meyers-Universal-References-in-Cpp11

https://stackoverflow.com/questions/17980570/pass-by-reference-constant-reference-rvalue-reference-or-constant-rvalue-refe

https://stackoverflow.com/questions/16216043/passing-r-value-as-non-const-reference-vs-warning-c4239

### 5. Sequence of including header files
https://stackoverflow.com/questions/2762568/c-c-include-file-order-best-practices

### 6. Order of calling the constructors
  [Order of calling the constructors] (https://www.youtube.com/watch?v=XkDEzfpdcSg&t=3248s) matters and the performance related to it

 ## ToDo's (not in sequence)
1. Implement --
2. Implement remove, erase
3. Implement find
4. Fix rvalue insert
5. copy, move, swap constructors 
6. operators like ==
7. Destruct the elements

 ## References
1. Apache implementation of red black tree: https://github.com/apache/stdcxx/blob/trunk/include/rw/_tree.h
2. GCC implementation: https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.1/stl__tree_8h-source.html
3. LLVM: https://github.com/google/libcxx/blob/27c836ff3a9c505deb9fd1616012924de8ff9279/include/__tree



