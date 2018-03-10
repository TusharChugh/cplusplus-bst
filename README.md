# BST implementatiion in C++

## Build and run the code  using bazel
1. Install bazel: https://docs.bazel.build/versions/master/install.html
2. Build the code: bazel build //test:bst-test
3. Run the tests: bazel run //test:bst-test

## More on bazel
1. Configuring google tests: https://docs.bazel.build/versions/master/cpp-use-cases.html

2. More of gtest and bazel: https://docs.bazel.build/versions/master/test-encyclopedia.html

## C++ reference
1. Code is based on c++ set implementation: http://en.cppreference.com/w/cpp/container/set

## C++ Iterators
1. Use bidiectional iterators
2. Two option to implement ++ operator with iterator (a. use of queue b. use parent pointer). 

 ## ToDo's
 1. Implement the basic api functions
 2. Add copy, move, swap, destructor to the bst class

 ## Notes:
 1. C++ set implementation uses red-black trees
