#include "vector3d.h"
#include <vector>
#include <iostream>

Vector3D::~Vector3D()
{
}

int Vector3D::add_integers(int firstNumber, int secondNumber)
{
    int summedNumber{0};
    summedNumber = (firstNumber + secondNumber);
    return summedNumber;
}

std::vector<double> Vector3D::make_vector(double firstNumber, double secondNumber, double thirdNumber)
{
    std::vector <double> newVector{0};
    newVector = {firstNumber, secondNumber, thirdNumber};
    return newVector;
}

std::vector<double> Vector3D::scale_vector(std::vector<double> initialVector, double scalingFactor)
{

    std::vector<int>::size_type vectorSize = initialVector.size();
    std::vector<double> resultantVector(vectorSize);
    //    std::cout << "Vector size: " << vectorSize << std::endl;

    for(unsigned i=0; i<vectorSize; i++)
    {
        resultantVector[i] = initialVector[i]*scalingFactor;
    }

    return resultantVector;
}

std::vector<double> Vector3D::add_vectors(std::vector<double> firstVector, std::vector<double> secondVector)
{
    std::vector<int>::size_type vectorSize = firstVector.size();
    std::vector<int>::size_type vectorSizeSecond = secondVector.size();
    std::vector<double> resultantVector(vectorSize);
    if (vectorSize==vectorSizeSecond)
    {
        for(unsigned i=0; i<vectorSize; i++)
        {
            resultantVector[i] = firstVector[i] + secondVector[i];
        }
    }
        else
    {
        std::cout << "ERROR: Vectors not same size" << std::endl;
    }
    return resultantVector;
}

