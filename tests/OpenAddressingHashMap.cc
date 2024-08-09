#include <gtest/gtest.h>
#include <algorithm>
#include "OpenAddressingHashMap.hpp"

// Test construction method
TEST(OpenAddressingHashMap, Construction)
{
    benn::OpenAddressingHashMap<int, int> map;
    EXPECT_EQ(map.size(), 0);
}

// Test insertion and retrieval of values
TEST(OpenAddressingHashMap, InsertAndRetrieve)
{
    benn::OpenAddressingHashMap<int, int> map;

    map.insert(std::pair<int, int>{1, 10});
    map.insert(std::pair<int, int>{2, 20});
    map.insert(std::pair<int, int>{3, 30});

    EXPECT_EQ(map[1], 10);
    EXPECT_EQ(map[2], 20);
    EXPECT_EQ(map[3], 30);

    map[4] = 40;
    map[5] = 50;
    map[6] = 60;
    EXPECT_EQ(map[4], 40);
    EXPECT_EQ(map[5], 50);
    EXPECT_EQ(map[6], 60);

    EXPECT_EQ(map.size(), 6);
}

// Test for updating a value
TEST(OpenAddressingHashMap, UpdateValue)
{
    benn::OpenAddressingHashMap<int, int> map;

    map.insert(std::pair<int, int>{1, 10});
    map.insert(std::pair<int, int>{1, 20});
    EXPECT_EQ(map[1], 20);

    map[2] = 20;
    map[2] = 30;
    EXPECT_EQ(map[2], 30);
}

// Test for removing key
TEST(OpenAddressingHashMap, RemovingKey)
{
    benn::OpenAddressingHashMap<int, int> map;

    map.insert(std::pair<int, int>{1, 10});
    map.remove(1);

    EXPECT_EQ(map.size(), 0);
}

// Test for handling non-existent keys
TEST(OpenAddressingHashMap, NonExistentKey)
{
    benn::OpenAddressingHashMap<int, int> map;

    EXPECT_EQ(map[0], 0);
    EXPECT_EQ(map[1], 0);
    EXPECT_EQ(map[2], 0);
}

// Test for resizing of hashmap
TEST(OpenAddressingHashMap, Resize)
{
    benn::OpenAddressingHashMap<int, int> map;
    EXPECT_EQ(map.getBucketCount(), 1);

    map[1] = 10;
    EXPECT_EQ(map.getBucketCount(), 2);

    map[2] = 20;
    EXPECT_EQ(map.getBucketCount(), 4);

    map[3] = 30;
    map[4] = 40;
    EXPECT_EQ(map.getBucketCount(), 8);

    map[5] = 50;
    map[6] = 60;
    map[7] = 70;
    map[8] = 80;
    EXPECT_EQ(map.getBucketCount(), 16);
}

// Test for existence of key
TEST(OpenAddressingHashMap, ExistenceOfKey)
{
    benn::OpenAddressingHashMap<int, int> map;

    EXPECT_EQ(map.count(0), 0);
    map[0] = 10;

    EXPECT_EQ(map.count(0), 1);
    EXPECT_EQ(map.count(1), 0);
    EXPECT_EQ(map.count(10), 0);
}