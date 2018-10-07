#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <sstream>
#include <vector>

class Vector3D
{
public:
    ~Vector3D();
    int Vector3D::add_integers(int firstNumber, int secondNumber);
    std::vector<double> Vector3D::make_vector(double firstNumber, double secondNumber, double thirdNumber);
    std::vector<double> Vector3D::scale_vector(std::vector <double> initialVector, double scalingFactor);
    std::vector<double> Vector3D::add_vectors(std::vector<double> firstVector, std::vector<double> secondVector);


protected:

private:

};
#endif // VECTOR3D_H
