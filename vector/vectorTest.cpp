#include "include/vector.h"

#include <array>
#include <iostream>

#include "gtest/gtest.h"

template <typename TypeT>
struct VectorTest : public testing::Test
{
    static const TypeT data[];
};

template <>
const int VectorTest<int>::data[] = {1,2,3,4};

template <>
const std::string VectorTest<std::string>::data[] = {"1", "2", "3", "someData"};

using Types = ::testing::Types<int, std::string>;
TYPED_TEST_SUITE(VectorTest, Types);

TYPED_TEST(VectorTest, DefaultConstructorNoThrow)
{
    EXPECT_NO_THROW(Vector<TypeParam>());
}

TYPED_TEST(VectorTest, ExplicitConstructorNoThrow)
{
    EXPECT_NO_THROW(Vector<TypeParam>(2));
}

TYPED_TEST(VectorTest, InsertWithDefaultAllocation)
{
    Vector<TypeParam> vec{};
    vec.insert(TestFixture::data[0]);
    EXPECT_EQ(TestFixture::data[0], vec[0]);
}

TYPED_TEST(VectorTest, Size)
{
    Vector<TypeParam> vec{};
    vec.insert(TestFixture::data[0]);
    EXPECT_EQ(1, vec.size());
}

TYPED_TEST(VectorTest, listInitializator)
{
    Vector<TypeParam> vec {TestFixture::data[0],TestFixture::data[1],TestFixture::data[2],TestFixture::data[3]};
    EXPECT_EQ(TestFixture::data[0], vec[0]);
    EXPECT_EQ(vec.size(), 4);
}

TYPED_TEST(VectorTest, CreateWithValue)
{
    Vector<TypeParam> vec {TestFixture::data[0]};
    vec.insert(TestFixture::data[1]);
    EXPECT_EQ(TestFixture::data[0], vec[0]);
    EXPECT_EQ(TestFixture::data[1], vec[1]);
}

TYPED_TEST(VectorTest, InsertWithSizeAllocationDuringInsert)
{
    Vector<TypeParam> vec(3);
    vec.insert(TestFixture::data[0]);
    vec.insert(TestFixture::data[1]);
    vec.insert(TestFixture::data[2]);
    EXPECT_EQ(vec[2], vec[2]);
}

TYPED_TEST(VectorTest, CopyConstructor)
{
    Vector<TypeParam> vec{};
    vec.insert(TestFixture::data[0]);
    vec.insert(TestFixture::data[1]);
    vec.insert(TestFixture::data[2]);

    auto vec2 {vec};
    EXPECT_EQ(vec, vec2);
}

TYPED_TEST(VectorTest, CopyAssignment)
{
    Vector<TypeParam> vec{};
    vec.insert(TestFixture::data[0]);
    vec.insert(TestFixture::data[1]);
    vec.insert(TestFixture::data[2]);

    const auto vec2 = vec;
    EXPECT_EQ(vec, vec2);
}

TYPED_TEST(VectorTest, SizeNotEqual)
{
    Vector<TypeParam> vec{};
    vec.insert(TestFixture::data[0]);
    vec.insert(TestFixture::data[1]);
    vec.insert(TestFixture::data[2]);

    Vector<TypeParam> vec2;

    vec2 = vec;
    vec2.insert(TestFixture::data[3]);
    EXPECT_NE(vec.size(), vec2.size());
}

TYPED_TEST(VectorTest, rangeBasedLoop)
{
    Vector<TypeParam> vec {TestFixture::data[0],TestFixture::data[1],TestFixture::data[2],TestFixture::data[3]};
    int count = 0;
    for(const auto& elem : TestFixture::data)
    {
        EXPECT_EQ(elem, vec[count++]);
    }
}

TYPED_TEST(VectorTest, moveCtor)
{
    Vector<TypeParam> vec {TestFixture::data[0],TestFixture::data[1],TestFixture::data[2],TestFixture::data[3]};
    const auto vCopy = vec;
    const auto v2 {std::move(vec)};
    EXPECT_EQ(v2, vCopy);
}

TYPED_TEST(VectorTest, constRangeBasedLoop)
{
    const Vector<TypeParam> vec {TestFixture::data[0],TestFixture::data[1],TestFixture::data[2],TestFixture::data[3]};
    int count = 0;
    for(const auto& elem : vec)
    {
        EXPECT_EQ(elem, vec[count++]);
    }
}