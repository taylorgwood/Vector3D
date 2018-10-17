#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H
#include "vector3d.h"
class Vector3;
class PhysicsObject;


class PhysicsWorld
{

public:
    ~PhysicsWorld();
    PhysicsWorld();

    Vector3 get_gravity() const;
    double get_fluid_density() const;
    void reset_gravity(PhysicsObject &physicsObject, Vector3 const gravity);
    void reset_fluid_density(double const fluidDensity);

private:
    Vector3 mGravity{0,0,-9.8};
    double mFluidDensity{1.275};
};

#endif // PHYSICSWORLD_H
