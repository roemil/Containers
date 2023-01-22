#include <gtest/gtest.h>

#include "vector.h"

#include <iostream>

TEST(VectorTest, DefaultConstructorNoThrow)
{
    EXPECT_NO_THROW(Utility::Vector());
}

TEST(VectorTest, ExplicitConstructorNoThrow)
{
    EXPECT_NO_THROW(Utility::Vector(2));
}

/*TEST(VectorTest, ExplicitConstructorThrow)
{
    EXPECT_THROW(Utility::Vector(-1000), std::bad_alloc);
}*/

TEST(VectorTest, InsertWithDefaultAllocation)
{
    auto vec {Utility::Vector()};
    vec.insert(1);
    EXPECT_EQ(1, vec[0]);
}

TEST(VectorTest, InsertWithCustomAllocation)
{
    auto vec {Utility::Vector(1)};
    vec.insert(1);
    EXPECT_EQ(1, vec[0]);
}

TEST(VectorTest, Size)
{
    auto vec {Utility::Vector(1)};
    vec.insert(1);
    EXPECT_EQ(1, vec.size());
}

TEST(VectorTest, InsertWithAllocationDuringInsert)
{
    auto vec {Utility::Vector(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);
    EXPECT_EQ(5, vec[2]);
}

TEST(VectorTest, CopyConstructor)
{
    auto vec {Utility::Vector(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    auto vec2 {vec};
    EXPECT_EQ(vec, vec2);
}

TEST(VectorTest, CopyAssignment)
{
    auto vec {Utility::Vector(1)};
    vec.insert(1);
    vec.insert(1);
    vec.insert(5);

    Utility::Vector vec2;

    vec2 = vec;
    EXPECT_EQ(vec, vec2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}