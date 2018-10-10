#include "vector3d.h"
// #include <vector>
// #include <iostream>

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

void Vector3::set_x(double x) const
{
    m_x = x;
}

void Vector3::set_y(double y) const
{
    m_y = y;
}

void Vector3::set_z(double z) const
{
    m_z = z;
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

Vector3 Vector3::operator/(const double &scalar)
{
    double x = get_x()/scalar;
    double y = get_y()/scalar;
    double z = get_z()/scalar;
    return Vector3(x, y, z);
}

Vector3 Vector3::cross(Vector3 const &secondVector)
{
    double x = (get_x()*secondVector.get_z() - get_z()*secondVector.get_y());
    double y = (get_z()*secondVector.get_x() - get_x()*secondVector.get_z());
    double z = (get_x()*secondVector.get_y() - get_x()*secondVector.get_x());
    return Vector3(x, y, z);
}

double Vector3::dot(Vector3 secondVector)
{
    double x = get_x()*secondVector.get_x();
    double y = get_y()*secondVector.get_y();
    double z = get_z()*secondVector.get_z();
    double dotProduct;
    dotProduct = (x+y+z);
    return dotProduct;
}

