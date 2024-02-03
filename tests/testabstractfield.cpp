//
// Created by Matthijs Rog on 11/19/2023.
//

#include "../googletest/include/gtest/gtest.h"
#include "../include/AbstractField.h"

TEST(Field, Constructor) {
    Field field(10, 20);
    EXPECT_EQ(field(0, 0), complex(0.0, 0.0));  // Assuming default is 0
    EXPECT_EQ(field.width(), 10);
    EXPECT_EQ(field.height(), 20);
}

TEST(Field, DimensionCheckingInitialization) {
    EXPECT_THROW(Field field(0, 20), std::invalid_argument);
    EXPECT_THROW(Field field(10, 0), std::invalid_argument);
    EXPECT_THROW(Field field(0, 0), std::invalid_argument);
    EXPECT_THROW(Field field(-1, 20), std::invalid_argument);
}

TEST(Field, CopyConstructor) {
    Field original(10, 10);
    original.fill(complex(1.0, 1.0));
    Field copy = original;

    EXPECT_EQ(copy(0, 0), original(0, 0));
    // Modify copy and check if original remains unchanged
    copy(0,0) = complex(2.0, 2.0);
    EXPECT_NE(copy(0, 0), original(0, 0));
}

TEST(Field, CopyAssignment) {
    Field original(10, 10);
    original.fill(complex(1.0, 1.0));
    Field copy(5, 5); // Different dimensions
    copy = original;

    EXPECT_EQ(copy(0, 0), original(0, 0));
    // Modify copy and check if original remains unchanged
    copy(0,0) = complex(2.0, 2.0);
    EXPECT_NE(copy(0, 0), original(0, 0));
}

TEST(Field, MoveAssignment) {
    Field original(10, 10);
    original.fill(complex(1.0, 1.0));
    Field moved(5, 5); // Different dimensions
    moved = std::move(original);

    EXPECT_EQ(moved(0, 0), complex(1.0, 1.0));
}

TEST(Field, MoveConstructor) {
    Field original(10, 10);
    original.fill(complex(1.0, 1.0));
    Field moved = std::move(original);

    EXPECT_EQ(moved(0, 0), complex(1.0, 1.0));
}

TEST(Field, Fill) {
    Field field(10, 10);
    field.fill(complex(1.0, 1.0));
    EXPECT_EQ(field(0, 0), complex(1.0, 1.0));
    EXPECT_EQ(field(9, 9), complex(1.0, 1.0));
}

TEST(Field, AccessOperatorConst) {
    const Field field(10, 10);
    EXPECT_EQ(field(0, 0), complex(0.0, 0.0));  // Assuming default is 0
}

TEST(Field, AccessOperator) {
    Field field(10, 10);
    field(0, 0) = complex(1.0, 1.0);
    EXPECT_EQ(field(0, 0), complex(1.0, 1.0));
}

TEST(Field, GetDimensions) {
    Field field(10, 20);
    EXPECT_EQ(field.width(), 10);
    EXPECT_EQ(field.height(), 20);
}

TEST(Mask, AccessOperatorConst) {
    const Mask mask(10, 10);
    EXPECT_EQ(mask(0, 0), false);
}

TEST(Mask, AccessOperator) {
    Mask mask(10, 10);
    mask(0, 0) = true;
    EXPECT_EQ(mask(0, 0), true);
}

TEST(Mask, NotOperator) {
    Mask mask(10, 10);
    mask.fill(true);
    mask(0, 0) = false;
    EXPECT_EQ(!mask(0, 0), true);
    EXPECT_EQ(!mask(1, 1), false);
}

TEST(Mask, OrOperator) {
    Mask mask1(10, 10);
    mask1.fill(true);
    mask1(0, 0) = false;
    mask1(1, 1) = false;
    Mask mask2(10, 10);
    mask2.fill(false);
    mask2(1, 1) = true;
    Mask result = mask1 || mask2;
    EXPECT_EQ(result(0, 0), false);
    EXPECT_EQ(result(1, 1), true);
    EXPECT_EQ(result(2, 2), true);

}

TEST(Field, DimensionCheckingInput) {
    Field field(10, 20);
    EXPECT_THROW(field(10, 20), std::out_of_range);
    EXPECT_THROW(field(9, 20), std::out_of_range);
    EXPECT_THROW(field(10, 19), std::out_of_range);
}

TEST(Field, ScalarAddition) {
    Field field(10, 10);
    field.fill(complex(1.0, 1.0));
    Field result = field + complex(1.0, 1.0);
    EXPECT_EQ(result(0, 0), complex(2.0, 2.0));
    EXPECT_EQ(result(9, 9), complex(2.0, 2.0));
}

TEST(Field, FieldAddition) {
    // Check both succesful addition and succesful throwing of std::invalid_argument when arguments don't match.
    Field field1(10, 10);
    field1.fill(complex(1.0, 1.0));
    Field field2(10, 10);
    field2.fill(complex(2.0, 2.0));
    Field result = field1 + field2;
    EXPECT_EQ(result(0, 0), complex(3.0, 3.0));

    Field field3(5, 5);
    EXPECT_THROW(field1 + field3, std::invalid_argument);
}

TEST(Field, ScalarSubtraction) {
    Field field(10, 10);
    field.fill(complex(1.0, 1.0));
    Field result = field - complex(1.0, 1.0);
    EXPECT_EQ(result(0, 0), complex(0.0, 0.0));
    EXPECT_EQ(result(9, 9), complex(0.0, 0.0));
}

TEST(Field, FieldSubtraction) {
    // Check both succesful subtraction and succesful throwing of std::invalid_argument when arguments don't match.
    Field field1(10, 10);
    field1.fill(complex(1.0, 1.0));
    Field field2(10, 10);
    field2.fill(complex(2.0, 2.0));
    Field result = field2 - field1;
    EXPECT_EQ(result(0, 0), complex(1.0, 1.0));

    Field field3(5, 5);
    EXPECT_THROW(field1 - field3, std::invalid_argument);
}

TEST(Field, ScalarMultiplication) {
    Field field(10, 10);
    field.fill(complex(1.0, 1.0));
    Field result = field * complex(2.0, 2.0);
    EXPECT_EQ(result(0, 0), complex(0.0, 4.0));
    EXPECT_EQ(result(9, 9), complex(0.0, 4.0));
}

TEST(Field, FieldMultiplication) {
    // Check both succesful multiplication and succesful throwing of std::invalid_argument when arguments don't match.
    Field field1(10, 10);
    field1.fill(complex(1.0, 1.0));
    Field field2(10, 10);
    field2.fill(complex(2.0, 2.0));
    Field result = field1 * field2;
    EXPECT_EQ(result(0, 0), complex(0.0, 4.0));

    Field field3(5, 5);
    EXPECT_THROW(field1 * field3, std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}