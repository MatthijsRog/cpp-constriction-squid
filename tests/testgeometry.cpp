//
// Created by Matthijs Rog on 12/15/2023.
//

#include "../googletest/include/gtest/gtest.h"
#include "../include/Geometry.h"

TEST(Geometry, GeometryInitialization) {
    Geometry geometry = Geometry(10, 10);

    EXPECT_EQ(geometry.inSuperconductor(1,1), true);
    EXPECT_EQ(geometry.inSuperconductor(0, 0), false);
}

TEST(Geometry, BoundaryRecognition) {
    Geometry geometry = Geometry(10, 10);

    EXPECT_EQ(geometry.onNorthernBoundary(1,1), false);
    EXPECT_EQ(geometry.onEasternBoundary(1,1), false);
    EXPECT_EQ(geometry.onWesternBoundary(8,8), false);
    EXPECT_EQ(geometry.onSouthernBoundary(8,8), false);

    EXPECT_EQ(geometry.onNorthernBoundary(8,8), true);
    EXPECT_EQ(geometry.onEasternBoundary(8,8), true);
    EXPECT_EQ(geometry.onWesternBoundary(1,1), true);
    EXPECT_EQ(geometry.onSouthernBoundary(1,1), true);
}

TEST(Geometry, VacuumRecognition) {
    Geometry geometry = Geometry(10, 10);

    EXPECT_EQ(geometry.onExteriorVacuum(1,1), false);
    EXPECT_EQ(geometry.onInteriorVacuum(1,1), false);
    EXPECT_EQ(geometry.onExteriorVacuum(0,0), true);
}