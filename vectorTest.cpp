#include <gtest/gtest.h>
#include "vector.h"
#include <iostream>

TEST(VectorTest, DefaultConstructorNoThrow)
{
    EXPECT_NO_THROW(Vector<int>());
}

TEST(VectorTest, ExplicitConstructorNoThrow)
{
    EXPECT_NO_THROW(Vector<int>(2));
}

/*TEST(VectorTest, ExplicitConstructorThrow)
{
    EXPECT_THROW(Vector<int>(-1000), std::bad_alloc);
}*/

TEST(VectorTest, InsertWithDefaultAllocation)
{
    auto vec {Vector<int>()};
    vec.insert(1);
    EXPECT_EQ(1, vec[0]);
}

TEST(VectorTest, InsertWithCustomAllocation)
{
    auto vec {Vector<int>(1)};
    vec.insert(1);
    EXPECT_EQ(1, vec[0]);
}

TEST(VectorTest, Size)
{
    auto vec {Vector<int>(1)};
    vec.insert(1);
    EXPECT_EQ(1, vec.size());
}

TEST(VectorTest, InsertWithAllocationDuringInsert)
{
    auto vec {Vector<int>(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);
    EXPECT_EQ(5, vec[2]);
}

TEST(VectorTest, CopyConstructor)
{
    auto vec {Vector<int>(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    auto vec2 {vec};
    EXPECT_EQ(vec, vec2);
}

TEST(VectorTest, CopyAssignment)
{
    auto vec {Vector<int>(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    Vector<int> vec2;

    vec2 = vec;
    EXPECT_EQ(vec, vec2);
}