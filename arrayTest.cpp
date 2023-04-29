#include <gtest/gtest.h>
#include "array.h"
#include <iostream>


TEST(ArrayTest, ctor)
{
    const std::size_t size = 2;
    Array<int, size> arr;
    static_assert(arr.size() == size);
}

TEST(ArrayTest, rangeBasedLoop)
{
    const std::size_t size = 5;
    Array<int, size> arr{1,2,3,4,5};
    std::size_t cnt = 0;
    for(const auto& elem : arr)
    {
        EXPECT_EQ(elem, arr[cnt++]);
    }
}

TEST(ArrayTest, at)
{
    const std::size_t size = 5;
    Array<int, size> arr{1,2,3,4,5};
    std::size_t cnt = 0;
    for(const auto& elem : arr)
    {
        EXPECT_EQ(elem, arr.at(cnt++));
    }
}

TEST(ArrayTest, atConst)
{
    const std::size_t size = 5;
    Array<int, size> arr{1,2,3,4,5};
    EXPECT_EQ(1, arr.at(0));
}

TEST(ArrayTest, front)
{
    const std::size_t size = 5;
    Array<int, size> arr{1,2,3,4,5};
    EXPECT_EQ(1, arr.front());
}

TEST(ArrayTest, back)
{
    const std::size_t size = 5;
    Array<int, size> arr{1,2,3,4,5};
    EXPECT_EQ(5, arr.back());
}

TEST(ArrayTest, empty)
{
    const std::size_t size = 0;
    Array<int, size> arr{};
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, data)
{
    const std::size_t size = 2;
    Array<int, size> arr{1,2};
    auto data = arr.data();
    EXPECT_EQ(1, data[0]);
}

TEST(ArrayTest, swap)
{
    const std::size_t size = 2;
    Array<int, size> arr{1,2};
    Array<int, size> arr2{2,1};
    arr.swap(arr2);
    EXPECT_EQ(arr[0], 2);
}

TEST(ArrayTest, swapOnNonClassFunc)
{
    const std::size_t size = 2;
    Array<int, size> arr{1,2};
    Array<int, size> arr2{2,1};
    swap(arr, arr2);
    EXPECT_EQ(arr[0], 2);
}
