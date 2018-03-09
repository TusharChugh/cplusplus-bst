cc_test(
  name = "bst-test",
  srcs = ["unit_tests.cc", "bst_construction.cpp"],
  copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        "//lib:bst",
    ],
)