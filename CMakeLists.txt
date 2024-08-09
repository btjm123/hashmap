
cmake_minimum_required(VERSION 3.10)

project(hashmap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/main.cpp
)

add_executable(hashmap ${SOURCES})

#add_executable(TestChaining tests/test_chaining.cpp src/ChainingHashMap.cpp)
#target_include_directories(TestChaining PRIVATE include)

#add_executable(TestOpenAddressing tests/test_open_addressing.cpp src/OpenAddressingHashMap.cpp)
#target_include_directories(TestOpenAddressing PRIVATE include)

# Enable testing
#enable_testing()

# Add tests
#add_test(NAME TestChaining COMMAND TestChaining)
#add_test(NAME TestOpenAddressing COMMAND TestOpenAddressing)
