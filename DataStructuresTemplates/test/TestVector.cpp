#include "gtest\gtest.h"
#include "..\include\vector.h"

using pkl::vector;

#define TESTVECTOR

#ifdef  TESTVECTOR

// Need to change the way capacity works, now it`s equal to size that is extremely inefficient, unless we use reserve();

class ConstructorsTest : public ::testing::Test {};

TEST_F(ConstructorsTest, DefaultConstructor) {
    vector<int> vec;

    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.begin(), nullptr);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.begin(), vec.end());
}

TEST_F(ConstructorsTest, InitializerList) {
    vector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 5);
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 5);

    vec = { 10, 20, 30, 40, 50 };

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.front(), 10);
    EXPECT_EQ(vec.back(), 50);
}

TEST_F(ConstructorsTest, FillConstructor) {
    vector<int> vec(2, 10);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.front(), 10);
    EXPECT_EQ(vec.back(), 10);
}

TEST_F(ConstructorsTest, CopyConstructor) {
    vector<int> vec = { 1, 2, 3, 4 };

    vector<int> vecTest(vec);

    ASSERT_NE(vec.begin(), vecTest.begin());
    ASSERT_NE(vec.end(), vecTest.end());

    EXPECT_EQ(vecTest.size(), 4);
    EXPECT_EQ(vecTest.front(), 1);
    EXPECT_EQ(vecTest.back(), 4);
    EXPECT_EQ(vecTest[1], 2);
    EXPECT_EQ(vecTest[2], 3);
}

TEST_F(ConstructorsTest, MoveConstructor) {
    vector<int> vec = { 1, 2, 3, 4 };

    vector<int> testVec(std::move(vec));

    ASSERT_EQ(vec.begin(), nullptr);
    ASSERT_EQ(vec.size(), 0);
    ASSERT_NE(vec.begin(), testVec.begin());

    EXPECT_EQ(testVec.size(), 4);
    EXPECT_EQ(testVec.front(), 1);
    EXPECT_EQ(testVec.back(), 4);
    EXPECT_EQ(testVec[1], 2);
    EXPECT_EQ(testVec[2], 3);
}

class AssignmentOperatorTest : public ::testing::Test {};

TEST_F(AssignmentOperatorTest, AssignmentOperator) {
    vector<int> vec = { 1, 2, 3, 4 };

    vector<int> testVec = { 5, 6, 7 };

    testVec = vec;

    ASSERT_NE(vec.begin(), testVec.begin());

    EXPECT_EQ(testVec.size(), 4);
    EXPECT_EQ(testVec.front(), 1);
    EXPECT_EQ(testVec.back(), 4);
    EXPECT_EQ(testVec[1], 2);
    EXPECT_EQ(testVec[2], 3);
}

TEST_F(AssignmentOperatorTest, MoveAssignmentOperator) {
    vector<int> vec = { 1, 2, 3, 4 };

    vector<int> testVec = { 5, 6, 7 };

    testVec = std::move(vec);

    ASSERT_NE(vec.begin(), testVec.begin());
    ASSERT_EQ(vec.begin(), nullptr);
    ASSERT_EQ(vec.size(), 0);

    EXPECT_EQ(testVec.size(), 4);
    EXPECT_EQ(testVec.front(), 1);
    EXPECT_EQ(testVec.back(), 4);
    EXPECT_EQ(testVec[1], 2);
    EXPECT_EQ(testVec[2], 3);
}

class ElementAccessTest : public ::testing::Test {};

TEST_F(ElementAccessTest, SquareBracketsTest) {
    vector<int> vec(2, 10);

    //ASSERT_THROW(list[2], ListException);

    //list.push_front(10);
    //list.push_back(20);

    //ASSERT_THROW(list[-3], ListException);
    //ASSERT_THROW(list[2], ListException);

    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 10);
}

TEST_F(ElementAccessTest, AtTest) {
    vector<int> vec;

    ASSERT_THROW(vec.at(3), std::logic_error);
    vec = { 15, 76, 323 };

    //list.push_front(10);
    //list.push_back(20);

    ASSERT_THROW(vec.at(-3), std::out_of_range);
    ASSERT_THROW(vec.at(20), std::out_of_range);

    EXPECT_EQ(vec.at(0), 15);
    EXPECT_EQ(vec.at(1), 76);
    EXPECT_EQ(vec.at(2), 323);
    EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST_F(ElementAccessTest, DataTest)
{
    vector<int> vec;

    int* pointer = vec.data();
    ASSERT_EQ(pointer, nullptr);

    vec = { 1, 2, 3, 4, 5 };

    pointer = vec.data();
    ASSERT_NE(pointer, nullptr);

    EXPECT_EQ(*(pointer), 1);
    EXPECT_EQ(*(pointer + 3), 4);

    pointer++;
    EXPECT_EQ(*(pointer), 2);

    pointer--;
    EXPECT_EQ(*(pointer), 1);

    pointer += 4;
    EXPECT_EQ(*(pointer), 5);
}

class CapacityTest : public ::testing::Test {};

TEST_F(CapacityTest, ReserveTest) {
    vector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(vec.capacity(), 5);

    vec.reserve(1000);
    EXPECT_EQ(vec.capacity(), 1000);
    EXPECT_EQ(vec.size(), 5);

    vec.reserve(100);
    EXPECT_EQ(vec.capacity(), 1000);
    EXPECT_EQ(vec.size(), 5);

    vector<int> vec2;
    vec2.reserve(100);

    EXPECT_EQ(vec2.capacity(), 100);
    EXPECT_EQ(vec2.size(), 0);
}

TEST_F(CapacityTest, ShrinkToFitTest) {
    vector<int> vec;

    vec.shrink_to_fit();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);

    vec = { 1, 2, 3, 4, 5 };

    vec.reserve(100);
    vec.push_back(10);
    vec.push_back(213);

    vec.shrink_to_fit();

    EXPECT_EQ(vec.size(), 7);
    EXPECT_EQ(vec.capacity(), 7);
}

TEST_F(CapacityTest, ResizeTest) {
    vector<int> vec = { 1, 2, 17, 8, 3, 18, 19, 123, 13 };

    vec.resize(2);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), 2);
    EXPECT_EQ(vec.capacity(), 9);

    vec.resize(8);
    EXPECT_EQ(vec.size(), 8);
    EXPECT_EQ(vec.back(), 0);
    EXPECT_EQ(vec.capacity(), 9);

    vec.resize(12);
    EXPECT_EQ(vec.size(), 12);
    EXPECT_EQ(vec.back(), 0);
    EXPECT_EQ(vec.capacity(), 12);

    vec.resize(18, 100);
    EXPECT_EQ(vec.size(), 18);
    EXPECT_EQ(vec.capacity(), 18);
    EXPECT_EQ(vec[12], 100);
    EXPECT_EQ(vec.back(), 100);

    vec.reserve(23);

    vec.resize(21, 100);
    EXPECT_EQ(vec.size(), 21);
    EXPECT_EQ(vec.capacity(), 23);
    EXPECT_EQ(vec[18], 100);
    EXPECT_EQ(vec[19], 100);
    EXPECT_EQ(vec.back(), 100);
}

class ModifiersTest : public ::testing::Test {};

TEST_F(ModifiersTest, PushBackTest) 
{
    vector<int> vec;

    vec.push_back(20);
   
    EXPECT_EQ(vec.capacity(), 1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.front(), 20);
    EXPECT_EQ(vec.back(), 20);

    vec.push_back(-23);
    EXPECT_EQ(vec.capacity(), 2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.front(), 20);
    EXPECT_EQ(vec.back(), -23);

    vec.push_back(13);
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_EQ(vec.size(), 3);

    vec = { 13, 14, 15, 16, 17 };
    vec.push_back(18);
    EXPECT_EQ(vec.capacity(), 10);
    EXPECT_EQ(vec.size(), 6);
    EXPECT_EQ(vec.front(), 13);
    EXPECT_EQ(vec.back(), 18);

    vec.push_back(19);
    EXPECT_EQ(vec.capacity(), 10);
    EXPECT_EQ(vec.size(), 7);
    EXPECT_EQ(vec.front(), 13);
    EXPECT_EQ(vec.back(), 19);

    vec.clear();
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_EQ(vec.size(), 0);
}

TEST_F(ModifiersTest, PopBackTest) 
{
    vector<int> vec = { 1, 2, 3, 4, 5 };

    vec.pop_back();

    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.back(), 4);

    vec.push_back(10);
    vec.push_back(11);
    vec.push_back(12);
    vec.pop_back();

    EXPECT_EQ(vec.size(), 6);
    EXPECT_EQ(vec.back(), 11);
}


TEST_F(ModifiersTest, AssignTest)
{
    vector<int> vec;
    vec.assign(2, 10);

    EXPECT_EQ(vec.capacity(), 2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), 10);
    EXPECT_EQ(vec.front(), 10);


    vec.assign(1, 20);
    EXPECT_EQ(vec.capacity(), 2);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.back(), 20);
    EXPECT_EQ(vec.front(), 20);

    vec.reserve(1000);
    vec.assign({ 1, 2, 3, 4, 5, 6, 7 });

    EXPECT_EQ(vec.capacity(), 1000);
    EXPECT_EQ(vec.size(), 7);
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 7);

    vec.assign(50, 20);
    EXPECT_EQ(vec.capacity(), 1000);
    EXPECT_EQ(vec.size(), 50);
    EXPECT_EQ(vec.front(), 20);
    EXPECT_EQ(vec.back(), 20);
}

#endif // TESTVECTOR