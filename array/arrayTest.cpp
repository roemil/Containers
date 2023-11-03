#include <gtest/gtest.h>
#include "include/array.h"
#include <iostream>


TEST(ArrayTest, ctor)
{
    constexpr std::size_t size = 2;
    Array<int, size> arr;
    static_assert(arr.size() == size);
}

TEST(ArrayTest, rangeBasedLoop)
{
    constexpr std::size_t size = 5;
    constexpr Array<int, size> arr{1,2,3,4,5};
    std::size_t cnt = 0;
    for(const auto elem : arr)
    {
        EXPECT_EQ(elem, arr[cnt++]);
    }
}

TEST(ArrayTest, at)
{
    constexpr std::size_t size = 5;
    constexpr Array<int, size> arr{1,2,3,4,5};
    std::size_t cnt = 0;
    for(const auto& elem : arr)
    {
        EXPECT_EQ(elem, arr.at(cnt++));
    }
}

TEST(ArrayTest, front)
{
    constexpr std::size_t size = 5;
    constexpr Array<int, size> arr{1,2,3,4,5};
    EXPECT_EQ(1, arr.front());
}

TEST(ArrayTest, back)
{
    constexpr std::size_t size = 5;
    constexpr Array<int, size> arr{1,2,3,4,5};
    EXPECT_EQ(5, arr.back());
}

TEST(ArrayTest, isEmpty)
{
    constexpr std::size_t size = 0;
    constexpr Array<int, size> arr{};
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, notEmpty)
{
    constexpr std::size_t size = 1;
    constexpr Array<int, size> arr{1};
    EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, data)
{
    constexpr std::size_t size = 2;
    constexpr Array<int, size> arr{1,2};
    EXPECT_EQ(1, *arr.data());
}

TEST(ArrayTest, swap)
{
    constexpr std::size_t size = 2;
    Array<int, size> arr{1,2};
    Array<int, size> arr2{2,1};
    arr.swap(arr2);
    EXPECT_EQ(arr[0], 2);
}

TEST(ArrayTest, swapOnNonClassFunc)
{
    constexpr std::size_t size = 2;
    Array<int, size> arr{1,2};
    Array<int, size> arr2{2,1};
    swap(arr, arr2);
    EXPECT_EQ(arr[0], 2);
}

TEST(ArrayTest, equal)
{
    constexpr std::size_t size = 3;
    constexpr Array<int, size> arr{1,2,3};
    constexpr Array<int, size> arr2{1,2,3};

    static_assert(arr == arr2, "Arrays not equal");
}

TEST(ArrayTest, notEqual)
{
    constexpr std::size_t size = 3;
    constexpr Array<int, size> arr{1,2,3};
    constexpr Array<int, size> arr2{1,2,4};

    static_assert(arr != arr2, "Arrays are equal when expecting not too");
}

TEST(ArrayTest, copyAssignment)
{
    constexpr std::size_t size = 3;
    constexpr Array<int, size> arr{1,2,3};

    constexpr auto arr2 = arr;

    static_assert(arr == arr2, "Arrays not equal");
}

TEST(ArrayTest, fill)
{
    constexpr std::size_t size = 3;
    Array<int, size> arr;
    arr.fill(3);
    for(const auto& elem : arr)
    {
        EXPECT_EQ(elem, 3);
    }
}

TEST(ArrayTest, size)
{
    constexpr std::size_t size = 3;
    constexpr Array<int, size> arr{1,2};
    static_assert(arr.size() == 3, "Size incorrect");
}

TEST(ArrayTest, maxSize)
{
    constexpr std::size_t size = 3;
    constexpr Array<int, size> arr{1,2};
    static_assert(arr.maxSize() == 3, "Size incorrect");
}
