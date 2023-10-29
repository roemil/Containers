#include <gtest/gtest.h>
#include "include/vector.h"
#include <iostream>

TEST(VectorTest, DefaultConstructorNoThrow)
{
    EXPECT_NO_THROW(Vector<int>());
}

TEST(VectorTest, ExplicitConstructorNoThrow)
{
    EXPECT_NO_THROW(Vector<int>(2));
}

TEST(VectorTest, InsertWithDefaultAllocation)
{
    Vector<int> vec {};
    vec.insert(1);
    EXPECT_EQ(1, vec[0]);
}

TEST(VectorTest, string)
{
    Vector<std::string> vec {};
    vec.insert("1");
    EXPECT_EQ("1", vec[0]);
}

TEST(VectorTest, listInitializator)
{
    Vector<int> vec {1,2,3,4};
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(vec.size(), 4);
}


TEST(VectorTest, CreateWithValue)
{
    Vector<int> vec {1};
    vec.insert(2);
    EXPECT_EQ(1, vec[0]);
}

TEST(VectorTest, Size)
{
    Vector<int> vec(1);
    vec.insert(1);
    EXPECT_EQ(1, vec.size());
}

TEST(VectorTest, InsertWithSizeAllocationDuringInsert)
{
    Vector<int> vec(1);
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);
    EXPECT_EQ(5, vec[2]);
}

TEST(VectorTest, CopyConstructor)
{
    Vector<int> vec {};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    auto vec2 {vec};
    EXPECT_EQ(vec, vec2);
}

TEST(VectorTest, CopyAssignment)
{
    Vector<int> vec {};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    Vector<int> vec2;

    vec2 = vec;
    EXPECT_EQ(vec, vec2);
}

TEST(VectorTest, SizeNotEqual)
{
    Vector<int> vec {};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    Vector<int> vec2;

    vec2 = vec;
    vec2.insert(5);
    EXPECT_NE(vec.size(), vec2.size());
}

TEST(VectorTest, rangeBasedLoop)
{
    const Vector<int> vec {12,3,4,5};
    int count = 0;
    for(const auto& elem : vec)
    {
        EXPECT_EQ(elem, vec[count++]);
    }
}

TEST(VectorTest, moveCtor)
{
    Vector<int> vec {12,3,4,5};
    const auto vCopy = vec;
    const auto v2 {std::move(vec)};
    EXPECT_EQ(v2, vCopy);
}

TEST(VectorTest, constRangeBasedLoop)
{
    const Vector<int> vec {12,3,4,5};
    int count = 0;
    for(const auto& elem : vec)
    {
        EXPECT_EQ(elem, vec[count++]);
    }
}