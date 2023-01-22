#include <gtest/gtest.h>

#include "SmartVector.h"

#include <iostream>

TEST(SmartVectorTest, DefaultConstructorNoThrow)
{
    EXPECT_NO_THROW(Utility::SmartVector<int>());
}

TEST(SmartVectorTest, ExplicitConstructorNoThrow)
{
    EXPECT_NO_THROW(Utility::SmartVector<int>(2));
}

/*TEST(SmartVectorTest, ExplicitConstructorThrow)
{
    EXPECT_THROW(Utility::SmartVector(-1000), std::bad_alloc);
}*/

TEST(SmartVectorTest, InsertWithDefaultAllocation)
{
    auto vec {Utility::SmartVector<int>()};
    vec.insert(1);
    EXPECT_EQ(1, vec[0]);
}

TEST(SmartVectorTest, InsertWithCustomAllocation)
{
    auto vec {Utility::SmartVector<int>(1)};
    vec.insert(1);
    EXPECT_EQ(1, vec[0]);
}

TEST(SmartVectorTest, Size)
{
    auto vec {Utility::SmartVector<int>(1)};
    vec.insert(1);
    EXPECT_EQ(1, vec.size());
}

TEST(SmartVectorTest, InsertWithAllocationDuringInsert)
{
    auto vec {Utility::SmartVector<int>(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);
    EXPECT_EQ(5, vec[2]);
}

TEST(SmartVectorTest, CopyConstructor)
{
    auto vec {Utility::SmartVector<int>(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    auto vec2 {vec};
    EXPECT_EQ(vec, vec2);
}

TEST(SmartVectorTest, MoveConstructor)
{
    auto vec {Utility::SmartVector<int>(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    auto vec2 = std::move(vec);
    EXPECT_EQ(1, vec2[0]);
    EXPECT_EQ(1, vec2[1]);
    EXPECT_EQ(5, vec2[2]);
}

TEST(SmartVectorTest, CopyAssignment)
{
    auto vec {Utility::SmartVector<int>(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    Utility::SmartVector<int> vec2;

    vec2 = vec;
    EXPECT_EQ(vec, vec2);
}
