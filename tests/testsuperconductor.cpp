//
// Created by Matthijs Rog on 11/19/2023.
//

#include "../googletest/include/gtest/gtest.h"
#include "../include/Superconductor.h"

TEST(SuperconductorTest, Constructor) {
    Superconductor superconductor(10, 20);
    EXPECT_EQ(superconductor.orderParameter()(0, 0), complex(0.0, 0.0));  // Assuming default is 0
    EXPECT_EQ(superconductor.orderParameter().width(), 10);
    EXPECT_EQ(superconductor.orderParameter().height(), 20);
}

TEST(SuperconductorTest, CopyConstructor) {
    Superconductor original(10, 10);
    original.orderParameter().fill(complex(1.0, 1.0));
    Superconductor copy = original;

    EXPECT_EQ(copy.orderParameter()(0, 0), original.orderParameter()(0, 0));
    // Modify copy and check if original remains unchanged
    copy.orderParameter()(0,0) = complex(2.0, 2.0);
    EXPECT_NE(copy.orderParameter()(0, 0), original.orderParameter()(0, 0));
}

TEST(SuperconductorTest, CopyAssignment) {
    Superconductor original(10, 10);
    original.orderParameter().fill(complex(1.0, 1.0));
    Superconductor copy(5, 5); // Different dimensions
    copy = original;

    EXPECT_EQ(copy.orderParameter()(0, 0), original.orderParameter()(0, 0));
    // Modify copy and check if original remains unchanged
    copy.orderParameter()(0,0) = complex(2.0, 2.0);
    EXPECT_NE(copy.orderParameter()(0, 0), original.orderParameter()(0, 0));
}

TEST(SuperconductorTest, MoveConstructor) {
    Superconductor original(10, 10);
    original.orderParameter().fill(complex(1.0, 1.0));
    Superconductor moved = std::move(original);

    EXPECT_EQ(moved.orderParameter()(0, 0), complex(1.0, 1.0));
}

TEST(SuperconductorTest, MoveAssignment) {
    Superconductor original(10, 10);
    original.orderParameter().fill(complex(1.0, 1.0));
    Superconductor moved(5, 5); // Different dimensions
    moved = std::move(original);

    EXPECT_EQ(moved.orderParameter()(0, 0), complex(1.0, 1.0));
}

TEST(SuperconductorTest, AccessOperatorConst) {
    const Superconductor superconductor(10, 10);
    EXPECT_EQ(superconductor.orderParameter()(0, 0), complex(0.0, 0.0));  // Assuming default is 0
    EXPECT_EQ(superconductor.linkingVariableX()(0,0), complex(0.0, 0.0));
    EXPECT_EQ(superconductor.linkingVariableY()(0,0), complex(0.0, 0.0));
    EXPECT_EQ(superconductor.fluxCellPhasor()(0,0), complex(0.0, 0.0));
}

TEST(SuperconductorTest, AccessOperatorNonConst) {
    Superconductor superconductor(10, 10);
    superconductor.orderParameter()(0, 0) = complex(1.0, 1.0);
    EXPECT_EQ(superconductor.orderParameter()(0, 0), complex(1.0, 1.0));
    superconductor.linkingVariableX()(0, 0) = complex(1.0, 1.0);
    EXPECT_EQ(superconductor.linkingVariableX()(0, 0), complex(1.0, 1.0));
    superconductor.linkingVariableY()(0, 0) = complex(1.0, 1.0);
    EXPECT_EQ(superconductor.linkingVariableY()(0, 0), complex(1.0, 1.0));
    superconductor.fluxCellPhasor()(0, 0) = complex(1.0, 1.0);
    EXPECT_EQ(superconductor.fluxCellPhasor()(0, 0), complex(1.0, 1.0));
}

TEST(SuperconductorTest, InvalidConstructorArguments) {
    EXPECT_THROW(Superconductor(-1, 10), std::invalid_argument);
    EXPECT_THROW(Superconductor(10, -1), std::invalid_argument);
    EXPECT_THROW(Superconductor(-1, -1), std::invalid_argument);
}



