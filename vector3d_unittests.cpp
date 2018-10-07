#include "gtest/gtest.h"
#include "vector3d.h"

//void print_tree(BinarySortTree &binarySortTree)
//{
//    std::ostringstream out;
//    binarySortTree.print(out);
//    std::cout<<out.str();
//}

TEST(TestSetup,addValuesToSum_getSummedValues)
{
    Vector3D vector3d;
    int expectedValue{3};
    int firstNumber{1};
    int secondNumber{2};
    int summedNumber{0};
    summedNumber = vector3d.add_integers(firstNumber,secondNumber);
    EXPECT_EQ(expectedValue,summedNumber);
}

TEST(VectorFormation,addValuesToVector_get3dVector)
{
    Vector3D vector3d;
    std::vector <double> expectedVector{1,2,3};
    double firstNumber{1};
    double secondNumber{2};
    double thirdNumber{3};
    std::vector <double> newVector = vector3d.make_vector(firstNumber,secondNumber, thirdNumber);
    EXPECT_EQ(expectedVector,newVector);
}

TEST(VectorScaling,multiplyVectorByValue_getScaledVector)
{
    Vector3D vector3d;
    std::vector <double> expectedVector{2,4,6};
    std::vector <double> initialVector{1,2,3};
    double scalingFactor{2};
    std::vector <double> newVector = vector3d.multiply_vector(initialVector, scalingFactor);
    EXPECT_EQ(expectedVector,newVector);
}
