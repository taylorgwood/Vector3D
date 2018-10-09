#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <sstream>
#include <vector>

class Vector3
{
public:
    ~Vector3();

    Vector3(double x, double y, double z);
    double get_x() const; // done
    double get_y() const;
    double get_z() const;
//    void set_x(double x); // decide if need
//    void set_y(double y);
//    void set_z(double z);
    Vector3 operator+(Vector3 const &secondVector);
    Vector3 operator-(Vector3 const &secondVector);
    Vector3 operator*(double const &scalar);

    Vector3 cross(Vector3 const &secondVector);
    double dot(Vector3 const &secondVector);

protected:

private:
    double m_x;
    double m_y;
    double m_z;

};
#endif // VECTOR3D_H

//    int Vector3D::add_integers(int firstNumber, int secondNumber);
//    std::vector<double> Vector3D::make_vector(double firstNumber, double secondNumber, double thirdNumber);
//    std::vector<double> Vector3D::scale_vector(std::vector <double> initialVector, double scalingFactor);
//    std::vector<double> Vector3D::add_vectors(std::vector<double> firstVector, std::vector<double> secondVector);
//    Vector3D Vector3D::make_vector3D(double firstNumber, double secondNumber, double thirdNumber);
//    Vector3D operator+(Vector3D firstVector, const secondVector);
