#include <gtest/gtest.h>
#include "include/SmartVector.h"
#include <iostream>

template <typename TypeT>
struct SmartVectorTest : public testing::Test
{
    static const TypeT data[];
};

template <>
const int SmartVectorTest<int>::data[] = {1,2,3,4};

template <>
const std::string SmartVectorTest<std::string>::data[] = {"1", "2", "3", "someData"};

using Types = ::testing::Types<int, std::string>;
TYPED_TEST_SUITE(SmartVectorTest, Types);

TYPED_TEST(SmartVectorTest, DefaultConstructorNoThrow)
{
    EXPECT_NO_THROW(SmartVector<int>());
}

TYPED_TEST(SmartVectorTest, ExplicitConstructorNoThrow)
{
    EXPECT_NO_THROW(SmartVector<int>(2));
}

TYPED_TEST(SmartVectorTest, InsertWithDefaultAllocation)
{
    SmartVector<TypeParam> vec{};
    vec.insert(TestFixture::data[0]);
    EXPECT_EQ(TestFixture::data[0], vec[0]);
}

TYPED_TEST(SmartVectorTest, InsertWithCustomAllocation)
{
    auto vec {SmartVector<TypeParam>(1)};
    vec.insert(TestFixture::data[0]);
    EXPECT_EQ(TestFixture::data[0], vec[0]);
}

TYPED_TEST(SmartVectorTest, Size)
{
    SmartVector<TypeParam> vec(1);
    vec.insert(TestFixture::data[0]);
    EXPECT_EQ(1, vec.size());
}

TYPED_TEST(SmartVectorTest, listInitializator)
{
    SmartVector<TypeParam> vec {TestFixture::data[0], TestFixture::data[1], TestFixture::data[2], TestFixture::data[3]};
    EXPECT_EQ(TestFixture::data[0], vec[0]);
    EXPECT_EQ(vec.size(), 4);
}

TYPED_TEST(SmartVectorTest, InsertWithAllocationDuringInsert)
{
    auto vec {SmartVector<TypeParam>(1)};
    vec.insert(TestFixture::data[0]);
    vec.insert(TestFixture::data[1]);
    vec.insert(TestFixture::data[2]);
    EXPECT_EQ(TestFixture::data[2], vec[2]);
}

TYPED_TEST(SmartVectorTest, CopyConstructor)
{
    SmartVector<TypeParam> vec(3);
    vec.insert(TestFixture::data[0]);
    vec.insert(TestFixture::data[1]);
    vec.insert(TestFixture::data[2]);

    const auto vec2 {vec};

    EXPECT_EQ(vec, vec2);
}

TYPED_TEST(SmartVectorTest, MoveConstructor)
{
    SmartVector<TypeParam> vec(3);
    vec.insert(TestFixture::data[0]);
    vec.insert(TestFixture::data[1]);
    vec.insert(TestFixture::data[2]);

    auto vec2 = std::move(vec);
    EXPECT_EQ(TestFixture::data[0], vec2[0]);
    EXPECT_EQ(TestFixture::data[1], vec2[1]);
    EXPECT_EQ(TestFixture::data[2], vec2[2]);
}

TYPED_TEST(SmartVectorTest, CopyAssignment)
{
    SmartVector<TypeParam> vec(3);
    vec.insert(TestFixture::data[0]);
    vec.insert(TestFixture::data[1]);
    vec.insert(TestFixture::data[2]);

    const auto vec2 = vec;

    EXPECT_EQ(vec, vec2);
}

TYPED_TEST(SmartVectorTest, NotEqual)
{
    SmartVector<TypeParam> vec(3);
    vec.insert(TestFixture::data[0]);
    vec.insert(TestFixture::data[1]);
    vec.insert(TestFixture::data[2]);

    auto vec2 = vec;
    vec2.insert(TestFixture::data[3]);

    EXPECT_NE(vec, vec2);
}

TYPED_TEST(SmartVectorTest, front)
{
    SmartVector<TypeParam> vec{TestFixture::data[2], TestFixture::data[1], TestFixture::data[0]};
    
    EXPECT_EQ(vec.front(), TestFixture::data[2]);
}

TYPED_TEST(SmartVectorTest, back)
{
    SmartVector<TypeParam> vec{TestFixture::data[2], TestFixture::data[1], TestFixture::data[0]};
    
    EXPECT_EQ(vec.back(), TestFixture::data[0]);
}

TYPED_TEST(SmartVectorTest, emplace_back)
{
    SmartVector<TypeParam> vec{};
    const auto last = vec.emplace_back(TestFixture::data[0], TestFixture::data[1], TestFixture::data[2]);

    EXPECT_EQ(TestFixture::data[0], vec[0]);
    EXPECT_EQ(TestFixture::data[1], vec[1]);
    EXPECT_EQ(TestFixture::data[2], vec[2]);

    EXPECT_EQ(TestFixture::data[2], last);
}