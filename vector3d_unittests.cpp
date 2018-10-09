#include "gtest/gtest.h"
#include "vector3d.h"

//void print_tree(BinarySortTree &binarySortTree)
//{
//    std::ostringstream out;
//    binarySortTree.print(out);
//    std::cout<<out.str();
//}

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


//TEST(TestSetup,addValuesToSum_getSummedValues)
//{
//    Vector3D vector3d;
//    int expectedValue{3};
//    int firstNumber{1};
//    int secondNumber{2};
//    int summedNumber{0};
//    summedNumber = vector3d.add_integers(firstNumber,secondNumber);
//    EXPECT_EQ(expectedValue,summedNumber);
//}

//TEST(VectorFormation,addValuesToVector_get3dVector)
//{
//    Vector3D vector3d;
//    std::vector<double> expectedVector{1,2,3};
//    double firstNumber{1};
//    double secondNumber{2};
//    double thirdNumber{3};
//    std::vector<double> newVector = vector3d.make_vector(firstNumber,secondNumber, thirdNumber);
//    EXPECT_EQ(expectedVector,newVector);
//}

//TEST(VectorScaling,multiplyVectorByValue_getScaledVector)
//{
//    Vector3D vector3d;

//    std::vector<double> initialVector{1,2,3};
//    double scalingFactor{2};
//    std::vector<double> expectedVector{2,4,6};
//    std::vector<double> newVector = vector3d.scale_vector(initialVector, scalingFactor);
//    EXPECT_EQ(expectedVector,newVector);
//}

//TEST(VectorAddition,inputTwoVectors_getMultipliedVector)
//{
//    Vector3D vector3d;
//    std::vector<double> firstVector{1,2,3};
//    std::vector<double> secondVector{1,2,5};
//    std::vector<double> expectedVector{2,4,8};
//    std::vector<double> newVector = vector3d.add_vectors(firstVector, secondVector);

//    EXPECT_EQ(expectedVector,newVector);
//}

//TEST(VectorFormation,addValuesToVector_get3dVector)
//{
//    Vector3D vector3d;
//    Vector3D expectedVector{1,2,3};
//    double firstNumber{1};
//    double secondNumber{2};
//    double thirdNumber{3};
//    Vector3D newVector = vector3d.make_vector3D(firstNumber,secondNumber, thirdNumber);
//    EXPECT_EQ(expectedVector,newVector);
//}
