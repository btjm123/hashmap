enable_testing()

include(GoogleTest)

function (add_test executableName fileName)
  add_executable(
    ${executableName}
    ${fileName}
  )
  target_link_libraries(
    ${executableName}
    GTest::gtest_main 
  )
 gtest_discover_tests(${executableName}) 
endfunction()

add_test(chaining_hashmap ChainingHashMap.cc)
add_test(open_addressing_hashmap OpenAddressingHashMap.cc)