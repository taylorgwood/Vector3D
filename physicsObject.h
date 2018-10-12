#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "vector3d.h"
class Vector3;

class PhysicsObject
{
public:
    ~PhysicsObject();
    PhysicsObject();
    PhysicsObject(Vector3 position, Vector3 velocity, Vector3 acceleration);

    double get_coefficient_of_restitution() const;
    Vector3 get_position() const;
    Vector3 get_velocity() const;
    Vector3 get_acceleration() const;
    Vector3 get_gravity() const;
    void set_position(Vector3 const position);
    void set_velocity(Vector3 const velocity);
    void set_acceleration(Vector3 const acceleration);
    void reset_gravity(Vector3 const gravity);
    void set_coefficient_of_restitution(double const coefficientOfRestitution);
    Vector3 get_drag_force() const;
    double get_mass() const;
    double get_radius() const;
    void update(double timestep);
    void box_collision();
    void create_sphere(Vector3 shapeLocation, float sphereRadius, Vector3 initialVelocity);

protected:

private:
    double  mCoefficientOfRestitution{0.8};
    Vector3 mPosition{0,0,0};
    Vector3 mVelocity{0,0,0};
    Vector3 mAcceleration{0,0,0};
    Vector3 mGravity{0,0,-9.8};
    double  mDragForce{0};
    double  mMass{1};
    double  mRadius{0};
    double  mBoxSize{5};

};
#endif // PHYSICSOBJECT_H


