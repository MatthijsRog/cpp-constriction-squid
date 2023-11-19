//
// Created by Matthijs Rog on 11/19/2023.
//

#include "../googletest/include/gtest/gtest.h"
#include "../include/Field.h"

TEST(FieldTest, Constructor) {
    Field field(10, 20);
    EXPECT_EQ(field(0, 0), complex(0.0, 0.0));  // Assuming default is 0
    EXPECT_EQ(field.width(), 10);
    EXPECT_EQ(field.height(), 20);
}

TEST(FieldTest, CopyConstructor) {
    Field original(10, 10);
    original.fill(complex(1.0, 1.0));
    Field copy = original;

    EXPECT_EQ(copy(0, 0), original(0, 0));
    // Modify copy and check if original remains unchanged
    copy(0,0) = complex(2.0, 2.0);
    EXPECT_NE(copy(0, 0), original(0, 0));
}

TEST(FieldTest, CopyAssignment) {
    Field original(10, 10);
    original.fill(complex(1.0, 1.0));
    Field copy(5, 5); // Different dimensions
    copy = original;

    EXPECT_EQ(copy(0, 0), original(0, 0));
    // Modify copy and check if original remains unchanged
    copy(0,0) = complex(2.0, 2.0);
    EXPECT_NE(copy(0, 0), original(0, 0));
}

TEST(FieldTest, MoveConstructor) {
    Field original(10, 10);
    original.fill(complex(1.0, 1.0));
    Field moved = std::move(original);

    EXPECT_EQ(moved(0, 0), complex(1.0, 1.0));
}

TEST(FieldTest, MoveAssignment) {
    Field original(10, 10);
    original.fill(complex(1.0, 1.0));
    Field moved(5, 5); // Different dimensions
    moved = std::move(original);

    EXPECT_EQ(moved(0, 0), complex(1.0, 1.0));
}

TEST(FieldTest, AccessOperatorConst) {
    const Field field(10, 10);
    EXPECT_EQ(field(0, 0), complex(0.0, 0.0));  // Assuming default is 0
}

TEST(FieldTest, AccessOperatorNonConst) {
    Field field(10, 10);
    field(0, 0) = complex(1.0, 1.0);
    EXPECT_EQ(field(0, 0), complex(1.0, 1.0));
}

TEST(FieldTest, AdditionOperator) {
    Field field1(10, 10);
    Field field2(10, 10);
    field1.fill(complex(1.0, 1.0));
    field2.fill(complex(2.0, 2.0));

    Field result = field1 + field2;
    EXPECT_EQ(result(0, 0), complex(3.0, 3.0));
}

// Similar tests for subtraction and multiplication
TEST(FieldTest, SubtractionOperator) {
    Field field1(10, 10);
    Field field2(10, 10);
    field1.fill(complex(1.0, 1.0));
    field2.fill(complex(2.0, 2.0));

    Field result = field1 - field2;
    EXPECT_EQ(result(0, 0), complex(-1.0, -1.0));
}

TEST(FieldTest, MultiplicationOperator) {
    Field field1(10, 10);
    complex value = complex(2.0, 2.0);

    field1.fill(complex(1.0, 1.0));
    Field result = field1 * value;

    EXPECT_EQ(result(0, 0), complex(0.0, 4.0));
}

TEST(FieldTest, Fill) {
    Field field(10, 10);
    field.fill(complex(2.0, 2.0));
    EXPECT_EQ(field(0, 0), complex(2.0, 2.0));
    // Maybe check more elements or the entire field
}

TEST(FieldTest, Width) {
    Field field(10, 20);
    EXPECT_EQ(field.width(), 10);
}

TEST(FieldTest, Height) {
    Field field(10, 20);
    EXPECT_EQ(field.height(), 20);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}