#include "physicsObject.h"

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

//Vector3 PhysicsObject::get_drag_force() const
//{
//    return mDragForce;
//}

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

void PhysicsObject::toggle_drag_force(bool onOff)
{
    mDragForceOn = onOff;
}

Vector3 PhysicsObject::calculate_drag_force()
{
    Vector3 dragForce{0,0,0};
    if(mDragForceOn)
    {
        double fluidDensity{1.275};
        double dragCoefficient{0.5};
        double pi{3.1416};
        double areaCrossSectional = get_radius()*get_radius()*pi;
        Vector3 velocity = get_velocity();
        Vector3 velocitySquared = velocity.vector_index_to_power(velocity,2);
        dragForce = velocitySquared*0.5*fluidDensity*dragCoefficient*areaCrossSectional;
        //        dragForce = velocity;
    }
    //    mDragForce = dragForce;
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
    //    calculate_drag_force();
    Vector3 newAcceleration = get_acceleration() - calculate_drag_force()/get_mass();
    Vector3 newVelocity = get_velocity() + newAcceleration*timestep;
    Vector3 newPosition = get_position() + newVelocity*timestep;
    set_acceleration(newAcceleration);
    set_velocity(newVelocity);
    set_position(newPosition);
}

void PhysicsObject::box_collision()
{
    double boxSize = mBoxSize;
    double coefficientOfRestitution{0.8};

    double detectionSize = boxSize-get_radius();


    if (mPosition.get_x() >= detectionSize)
    {
        mPosition.set_x(detectionSize);
        double velocityAfterBounce{-mVelocity.get_x()*coefficientOfRestitution};
        mVelocity.set_x(velocityAfterBounce);
    }
    if(mPosition.get_y() >= detectionSize)
    {
        mPosition.set_y(detectionSize);
        double velocityAfterBounce{-mVelocity.get_y()*coefficientOfRestitution};
        mVelocity.set_y(velocityAfterBounce);
    }
    if(mPosition.get_z() >= detectionSize)
    {
        mPosition.set_z(detectionSize);
        double velocityAfterBounce{-mVelocity.get_z()*coefficientOfRestitution};
        mVelocity.set_z(velocityAfterBounce);
    }
    if (mPosition.get_x() <= -detectionSize)
    {
        mPosition.set_x(-detectionSize);
        double velocityAfterBounce{-mVelocity.get_x()*coefficientOfRestitution};
        mVelocity.set_x(velocityAfterBounce);
    }
    if(mPosition.get_y() <= -detectionSize)
    {
        mPosition.set_y(-detectionSize);
        double velocityAfterBounce{-mVelocity.get_y()*coefficientOfRestitution};
        mVelocity.set_y(velocityAfterBounce);
    }
    if(mPosition.get_z() <= -detectionSize)
    {
        mPosition.set_z(-detectionSize);
        double velocityAfterBounce{-mVelocity.get_z()*coefficientOfRestitution};
        mVelocity.set_z(velocityAfterBounce);
    }
}

//void PhysicsObject::create_sphere(Vector3 shapeLocation, float sphereRadius, Vector3 initialVelocity)
//{
//    mPosition = shapeLocation;
//    mRadius = sphereRadius;
//    mVelocity = initialVelocity;
//}

void PhysicsObject::move_back_from_wall(Vector3 directionOfMove)
{
    directionOfMove = directionOfMove.normalize();
    Vector3 moveDistance = directionOfMove*get_radius();
    Vector3 newPosition = get_position()+moveDistance;
    set_position(newPosition);
}



