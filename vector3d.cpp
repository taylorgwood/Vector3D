#include "vector3d.h"
#include <vector>

int Vector3D::add_integers(int firstNumber, int secondNumber)
{
    int summedNumber{0};
    summedNumber = (firstNumber + secondNumber);
    return summedNumber;
}

std::vector <double> Vector3D::make_vector(double firstNumber, double secondNumber, double thirdNumber)
{
    std::vector <double> newVector{0};
    newVector = {firstNumber, secondNumber, thirdNumber};
    return newVector;
}

Vector3D::~Vector3D()
{
}
