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
