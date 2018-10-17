#include "physicsObject.h"
#include "physicsworld.h"

PhysicsObject::~PhysicsObject()
{
}

PhysicsObject::PhysicsObject()
{
    mAcceleration = mGravity;
}

PhysicsObject::PhysicsObject(Vector3 position, Vector3 velocity, Vector3 acceleration): mPosition{position}, mVelocity{velocity}, mAcceleration{acceleration}
{
}

PhysicsObject::PhysicsObject(Vector3 position, Vector3 velocity, Vector3 acceleration, float radius, double mass, double cOfR, double fluidDensity)
{
    set_position(position);
    set_velocity(velocity);
    set_acceleration(acceleration);
    set_radius(radius);
    set_mass(mass);
    set_coefficient_of_restitution(cOfR);
    set_fluid_density(fluidDensity);
}

double PhysicsObject::get_coefficient_of_restitution() const
{
    return mCoefficientOfRestitution;
}

Vector3 PhysicsObject::get_position() const
{
    return mPosition;
}

Vector3 PhysicsObject::get_velocity() const
{
    return mVelocity;
}

Vector3 PhysicsObject::get_acceleration() const
{
    return mAcceleration;
}

Vector3 PhysicsObject::get_gravity() const
{
    return mGravity;
}

double PhysicsObject::get_fluid_density() const
{
    return mFluidDensity;
}

void PhysicsObject::set_position(Vector3 const position)
{
    mPosition = position;
}

void PhysicsObject::set_velocity(Vector3 const velocity)
{
    mVelocity = velocity;
}

void PhysicsObject::set_acceleration(Vector3 const acceleration)
{
    mAcceleration = acceleration;
}

void PhysicsObject::reset_gravity(Vector3 const gravity)
{
    Vector3 newAcceleration = mAcceleration-mGravity;
    Vector3 newGravity = gravity;
    newAcceleration = newAcceleration + gravity;
    mAcceleration = newAcceleration;
    mGravity = gravity;
}

void PhysicsObject::set_coefficient_of_restitution(double const coefficientOfRestitution)
{
    mCoefficientOfRestitution = coefficientOfRestitution;
}

void PhysicsObject::set_radius(float const radius)
{
    mRadius = radius;
}

void PhysicsObject::set_mass(float const mass)
{
    mMass = mass;
}

void PhysicsObject::set_fluid_density(float const fluidDensity)
{
    mFluidDensity = fluidDensity;
}

void PhysicsObject::toggle_drag_force(bool onOff)
{
    mDragForceOn = onOff;
}

Vector3 PhysicsObject::calculate_drag_force()
{
    Vector3 dragForce{0,0,0};
    if(mDragForceOn)
    {
        double fluidDensity = mFluidDensity;
        double dragCoefficient{0.5};
        double pi{3.1416};
        double areaCrossSectional = get_radius()*get_radius()*pi;
        Vector3 velocity = get_velocity();
        Vector3 velocitySquared = velocity.vector_index_to_power(velocity,2);

        if (velocity.get_x() > 0)
        {
            velocitySquared.set_x(velocitySquared.get_x()*-1);
        }
        if (velocity.get_y() > 0)
        {
            velocitySquared.set_y(velocitySquared.get_y()*-1);
        }
        if (velocity.get_z() > 0)
        {
            velocitySquared.set_z(velocitySquared.get_z()*-1);
        }

        dragForce = velocitySquared*0.5*fluidDensity*dragCoefficient*areaCrossSectional;
    }
    return dragForce;
}

double PhysicsObject::get_mass() const
{
    return mMass;
}

float PhysicsObject::get_radius() const
{
    return mRadius;
}

void PhysicsObject::update(double timestep)
{   
    Vector3 newPosition = get_position() + get_velocity()*timestep;
    Vector3 newVelocity = get_velocity() + get_acceleration()*timestep;
    Vector3 newAcceleration = get_gravity() + calculate_drag_force()/get_mass();
    set_acceleration(newAcceleration);
    set_velocity(newVelocity);
    set_position(newPosition);
    box_collision();
}

void PhysicsObject::box_collision()
{
    double boxSize = mBoxSize;
    double coefficientOfRestitution = mCoefficientOfRestitution;

    double detectionSize = boxSize-get_radius();
    if (mPosition.get_x() >= detectionSize)
    {
        mPosition.set_x(detectionSize);
        double velocityAfterBounce{-mVelocity.get_x()*coefficientOfRestitution};
        mVelocity.set_x(velocityAfterBounce);
    }
    else if (mPosition.get_x() <= -detectionSize)
    {
        mPosition.set_x(-detectionSize);
        double velocityAfterBounce{-mVelocity.get_x()*coefficientOfRestitution};
        mVelocity.set_x(velocityAfterBounce);
    }
    if(mPosition.get_y() >= detectionSize)
    {
        mPosition.set_y(detectionSize);
        double velocityAfterBounce{-mVelocity.get_y()*coefficientOfRestitution};
        mVelocity.set_y(velocityAfterBounce);
    }
    else if(mPosition.get_y() <= -detectionSize)
    {
        mPosition.set_y(-detectionSize);
        double velocityAfterBounce{-mVelocity.get_y()*coefficientOfRestitution};
        mVelocity.set_y(velocityAfterBounce);
    }
    if(mPosition.get_z() >= detectionSize)
    {
        mPosition.set_z(detectionSize);
        double velocityAfterBounce{-mVelocity.get_z()*coefficientOfRestitution};
        mVelocity.set_z(velocityAfterBounce);
    }
    else if(mPosition.get_z() <= -detectionSize)
    {
        mPosition.set_z(-detectionSize);
        double velocityAfterBounce{-mVelocity.get_z()*coefficientOfRestitution};
        mVelocity.set_z(velocityAfterBounce);
    }
}

void PhysicsObject::create_sphere(Vector3 shapePosition, float sphereRadius, Vector3 initialVelocity)
{
    mRadius = sphereRadius;
    PhysicsObject sphere(shapePosition, initialVelocity, mGravity);
    //mCoefficientOfRestitution = coefficientOfRestitution;
}

void PhysicsObject::move_back_from_wall(Vector3 directionOfMove)
{
    double detectionSize = mBoxSize-get_radius();
    //    directionOfMove = directionOfMove.normalize();
    Vector3 newPosition = directionOfMove*(-1*detectionSize);
    //    Vector3 newPosition = get_position()+moveDistance;
    set_position(newPosition);
}



