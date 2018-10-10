#include "gtest/gtest.h"
#include "vector3d.h"
#include "physicsObject.h"

void EXPECT_EQ_VECTORS(const Vector3& firstVector, const Vector3& secondVector)
{
    EXPECT_DOUBLE_EQ(firstVector.get_x(), secondVector.get_x());
    EXPECT_DOUBLE_EQ(firstVector.get_y(), secondVector.get_y());
    EXPECT_DOUBLE_EQ(firstVector.get_z(), secondVector.get_z());
}

TEST(VectorFormation,givenThreeNumbers_getVector)
{
    double x1{1};
    double y1{2};
    double z1{3};
    Vector3 formedVector{x1,y1,z1};
    EXPECT_EQ(x1,formedVector.get_x());
    EXPECT_EQ(y1,formedVector.get_y());
    EXPECT_EQ(z1,formedVector.get_z());
}

TEST(VectorAddition,givenTwoVectorsToAdd_getAddedVector)
{
    double x1{1};
    double y1{2};
    double z1{3};
    double x2{2};
    double y2{3};
    double z2{4};
    double x3{3};
    double y3{5};
    double z3{7};
    Vector3 firstVector{x1, y1, z1};
    Vector3 secondVector{x2, y2, z2};
    Vector3 expectedVector{x3, y3, z3};
    Vector3 addedVector = (firstVector+secondVector);
    EXPECT_EQ_VECTORS(expectedVector,addedVector);
}

TEST(VectorSubtraction,givenTwoVectorsToSubstract_getResultantVector)
{
    double x1{1};
    double y1{2};
    double z1{3};
    double x2{2};
    double y2{3};
    double z2{1};
    double x3{-1};
    double y3{-1};
    double z3{2};
    Vector3 firstVector{x1, y1, z1};
    Vector3 secondVector{x2, y2, z2};
    Vector3 expectedVector{x3, y3, z3};
    Vector3 substractedVector = (firstVector-secondVector);
    EXPECT_EQ_VECTORS(expectedVector,substractedVector);
}

TEST(VectorMulitplication,givenVectorandScalar_getScaledVector)
{
    double x1{1};
    double y1{2};
    double z1{3};
    double x2{2.5};
    double y2{5};
    double z2{7.5};
    double scalar{2.5};
    Vector3 firstVector{x1, y1, z1};
    Vector3 expectedVector{x2, y2, z2};
    Vector3 scaledVector = (firstVector*scalar);
    EXPECT_EQ_VECTORS(expectedVector,scaledVector);
}

TEST(VectorDotProduct,givenTwoVectors_getDotProduct)
{
    double x1{1};
    double y1{2};
    double z1{3};
    double x2{2};
    double y2{3};
    double z2{1};
    Vector3 firstVector{x1, y1, z1};
    Vector3 secondVector{x2, y2, z2};
    double expectedResult{11};
    double dotProdutResult = firstVector.dot(secondVector);
    EXPECT_DOUBLE_EQ(dotProdutResult,expectedResult);
}
