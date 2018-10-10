#include "physicsObject.h"

PhysicsObject::~PhysicsObject()
{
}

double PhysicsObject::get_CoefficientOfRestitution() const
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

Vector3 PhysicsObject::get_drag_force() const
{
    Vector3 dragForce{0,0,0};
    //dragForce = (1/2)*density*(get_v()*get_v())*get_CoefficientOfRestitution()*get_radius();
    return dragForce;
}

double PhysicsObject::get_mass() const
{
    return mMass;
}

double PhysicsObject::get_radius() const
{
    return mRadius;
}


void PhysicsObject::update(double timestep)
{
    mPosition = get_position() + get_velocity()*timestep;
    mVelocity = get_velocity() + get_acceleration()*timestep;
    mAcceleration = get_acceleration() + get_drag_force()/get_mass();
}

void PhysicsObject::box_collision()
{
    double detectionSize = mBoxSize-get_radius();
    if ((mPosition.get_x() >= detectionSize) || (mPosition.get_x() <= -detectionSize))
    {
        mPosition.set_x(detectionSize);
        double velocityAfterBounce{-mVelocity.get_x()*mCoefficientOfRestitution};
        mVelocity.set_x(velocityAfterBounce);
    }
    else if((mPosition.get_y() >= detectionSize) || (mPosition.get_y() <= -detectionSize))
    {
        mPosition.set_y(detectionSize);
        double velocityAfterBounce{-mVelocity.get_y()*mCoefficientOfRestitution};
        mVelocity.set_y(velocityAfterBounce);
    }
    else if((mPosition.get_z() >= detectionSize) || (mPosition.get_z() <= -detectionSize))
    {
        mPosition.set_z(detectionSize);
        double velocityAfterBounce{-mVelocity.get_z()*mCoefficientOfRestitution};
        mVelocity.set_z(velocityAfterBounce);
    }
    else{}
}

void PhysicsObject::create_sphere(Vector3 shapeLocation, float sphereRadius, Vector3 initialVelocity)
{
    mPosition = shapeLocation;
    mRadius = sphereRadius;
    mVelocity = initialVelocity;
}


