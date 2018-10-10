#ifndef PHYSICS_H
#define PHYSICS_H
#include "vector3d.h"
class Vector3;

class PhysicsObject
{
public:
    ~PhysicsObject();

    double get_CoefficientOfRestitution() const;
    Vector3 get_position() const;
    Vector3 get_velocity() const;
    Vector3 get_acceleration() const;
    Vector3 get_drag_force() const;
    double get_mass() const;
    double get_radius() const;
    void update(double timestep);
    void box_collision();
    double mBoxSize{5};
    void create_sphere(Vector3 shapeLocation, float sphereRadius, Vector3 initialVelocity);

protected:

private:
    double  mCoefficientOfRestitution{0.8};
    Vector3 mPosition{0,0,0};
    Vector3 mVelocity{0,0,0};
    Vector3 mAcceleration{0,0,0};
    double  mDragForce{0};
    double  mMass{0};
    double  mRadius{0};

};
#endif // PHYSICS_H


