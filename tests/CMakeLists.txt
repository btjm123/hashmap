enable_testing()

add_executable(
  chaining_hashmap
  ChainingHashMap.cc
)

add_executable(
  open_addressing_hashmap
  OpenAddressingHashMap.cc
)
target_link_libraries(
  chaining_hashmap
  GTest::gtest_main
)
target_link_libraries(
  open_addressing_hashmap
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(chaining_hashmap)
gtest_discover_tests(open_addressing_hashmap)