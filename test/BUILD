cc_test(
  name = "bst-test",
  srcs = ["unit_tests.cc", "bst_construction.cpp", "bst_iterator_test.cpp"],
  copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        "//lib:bst",
    ],
)