#ifndef VECTOR3D_H
#define VECTOR3D_H
//#include "physics.h"
class PhysicsObject;

class Vector3
{
public:
    ~Vector3();

    Vector3(double x, double y, double z);
    double get_x() const; // done
    double get_y() const;
    double get_z() const;
    void set_x(double const x); // decide if need
    void set_y(double const y);
    void set_z(double const z);
    Vector3 operator+(Vector3 const &secondVector);
    Vector3 operator-(Vector3 const &secondVector);
    Vector3 operator*(double const &scalar);
    Vector3 operator/(double const &scalar);

    Vector3 cross(Vector3 const &secondVector);
    double dot(Vector3 secondVector);

protected:

private:
    double m_x{0};
    double m_y{0};
    double m_z{0};

};
#endif // VECTOR3D_H
