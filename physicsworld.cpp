#include "physicsworld.h"
#include "physicsObject.h"

PhysicsWorld::PhysicsWorld()
{

}


void PhysicsWorld::reset_gravity(PhysicsObject &physicsObject, Vector3 const gravity)
{
    Vector3 newAcceleration = physicsObject.get_acceleration()-mGravity;
    Vector3 newGravity = gravity;
    newAcceleration = newAcceleration + gravity;
    physicsObject.set_acceleration(newAcceleration);
    mGravity = gravity;
}

Vector3 PhysicsWorld::get_gravity() const
{
    return mGravity;
}

double PhysicsWorld::get_fluid_density() const
{
    return mFluidDensity;
}

void PhysicsWorld::reset_fluid_density(double const fluidDensity)
{
    mFluidDensity = fluidDensity;
}
