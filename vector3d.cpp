#include "vector3d.h"
#include <vector>
#include <iostream>

Vector3::~Vector3()
{
}

Vector3::Vector3(double x, double y, double z) : m_x{x}, m_y{y}, m_z{z}
{
}

double Vector3::get_x() const
{
    return m_x;
}

double Vector3::get_y() const
{
    return m_y;
}

double Vector3::get_z() const
{
    return m_z;
}

Vector3 Vector3::operator+(const Vector3 &secondVector)
{
    double x = get_x() + secondVector.get_x();
    double y = get_y() + secondVector.get_y();
    double z = get_z() + secondVector.get_z();
    return Vector3(x, y, z);
}

Vector3 Vector3::operator-(const Vector3 &secondVector)
{
    double x = get_x() - secondVector.get_x();
    double y = get_y() - secondVector.get_y();
    double z = get_z() - secondVector.get_z();
    return Vector3(x, y, z);
}

Vector3 Vector3::operator*(const double &scalar)
{
    double x = get_x()*scalar;
    double y = get_y()*scalar;
    double z = get_z()*scalar;
    return Vector3(x, y, z);
}

Vector3 Vector3::cross(Vector3 const &secondVector)
{
    double x = (get_x()*secondVector.get_z() - get_z()*secondVector.get_y());
    double y = (get_z()*secondVector.get_x() - get_x()*secondVector.get_z());
    double z = (get_x()*secondVector.get_y() - get_x()*secondVector.get_x());
    return Vector3(x, y, z);
}

double Vector3::dot(Vector3 const &secondVector)
{
    double x = get_x()*secondVector.get_x();
    double y = get_y()*secondVector.get_y();
    double z = get_z()*secondVector.get_z();
    double dotProduct;
    dotProduct = (x+y+z);
    return dotProduct;
}

//int Vector3::add_integers(int firstNumber, int secondNumber)
//{
//    int summedNumber{0};
//    summedNumber = (firstNumber + secondNumber);
//    return summedNumber;
//}

//std::vector<double> Vector3D::make_vector(double firstNumber, double secondNumber, double thirdNumber)
//{
//    std::vector <double> newVector{0};
//    newVector = {firstNumber, secondNumber, thirdNumber};
//    return newVector;
//}

//std::vector<double> Vector3D::scale_vector(std::vector<double> initialVector, double scalingFactor)
//{

//    std::vector<int>::size_type vectorSize = initialVector.size();
//    std::vector<double> resultantVector(vectorSize);
//    //    std::cout << "Vector size: " << vectorSize << std::endl;

//    for(unsigned i=0; i<vectorSize; i++)
//    {
//        resultantVector[i] = initialVector[i]*scalingFactor;
//    }

//    return resultantVector;
//}

//std::vector<double> Vector3D::add_vectors(std::vector<double> firstVector, std::vector<double> secondVector)
//{
//    std::vector<int>::size_type vectorSize = firstVector.size();
//    std::vector<int>::size_type vectorSizeSecond = secondVector.size();
//    std::vector<double> resultantVector(vectorSize);
//    if (vectorSize==vectorSizeSecond)
//    {
//        for(unsigned i=0; i<vectorSize; i++)
//        {
//            resultantVector[i] = firstVector[i] + secondVector[i];
//        }
//    }
//        else
//    {
//        std::cout << "ERROR: Vectors not same size" << std::endl;
//    }
//    return resultantVector;
//}

//Vector3D Vector3D::make_vector3D(double firstNumber, double secondNumber, double thirdNumber)
//{
//    Vector3D newVector {firstNumber};
//    return newVector;
//}

//Vector3D operator+(Vector3D firstVector, const secondVector)
//{
//    // use the Cents constructor and operator+(int, int)
//        // we don't need direct access to private members here
//    return Vector3D(firstVector + secondVector);
//}
