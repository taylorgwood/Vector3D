#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "vector3d.h"
class Vector3;
class PhysicsWorld;

class PhysicsObject
{
public:
    ~PhysicsObject();
    PhysicsObject();
    PhysicsObject(Vector3 position, Vector3 velocity, Vector3 acceleration);
    PhysicsObject(Vector3 position, Vector3 velocity, Vector3 acceleration, float radius, double mass, double cOfR, double fluidDensity);
    double  get_coefficient_of_restitution() const;
    Vector3 get_position() const;
    Vector3 get_velocity() const;
    Vector3 get_acceleration() const;
    Vector3 get_gravity() const;
    double  get_fluid_density() const;
//    Vector3 get_drag_force() const;
    void set_position(Vector3 const position);
    void set_velocity(Vector3 const velocity);
    void set_acceleration(Vector3 const acceleration);
    void reset_gravity(Vector3 const gravity);
    void set_coefficient_of_restitution(double const coefficientOfRestitution);
    void set_radius(float const radius);
    void set_mass(float const mass);
    void set_fluid_density(float const fluidDensity);
    void toggle_drag_force(bool onOff);
    Vector3 calculate_drag_force();

    double get_mass() const;
    float get_radius() const;
    void update(double timestep);
    void box_collision();
    void create_sphere(Vector3 shapeLocation, float sphereRadius, Vector3 initialVelocity);
    void move_back_from_wall(Vector3 directionOfMove);
//    void create_world();

protected:

private:
    double  mCoefficientOfRestitution{0.8};
    Vector3 mPosition{0,0,0};
    Vector3 mVelocity{0,0,0};
    Vector3 mAcceleration{0,0,0};
    Vector3 mGravity{0,0,-9.8};
    double  mFluidDensity{1.275};
    Vector3 mDragForce{0,0,0};
    bool    mDragForceOn{1};
    double  mMass{10};
    float   mRadius{1};
    double  mBoxSize{5};

};
#endif // PHYSICSOBJECT_H


