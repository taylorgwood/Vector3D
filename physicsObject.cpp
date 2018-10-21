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
    reset_gravity(acceleration);
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

void PhysicsObject::set_mass(const double mass)
{
    mMass = mass;
}

void PhysicsObject::set_fluid_density(const double fluidDensity)
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
    double x{1};
    double y{2};
    double z{3};

    double detectionSize = boxSize-get_radius();
    if (mPosition.get_x() >= detectionSize || mPosition.get_x() <= -detectionSize)
    {
        mPosition.set_x(detectionSize*mPosition.sign().get_x());
        set_velocity_after_bounce(1);
    }
    if(mPosition.get_y() >= detectionSize || mPosition.get_y() <= -detectionSize)
    {
        mPosition.set_y(detectionSize*mPosition.sign().get_y());
        set_velocity_after_bounce(2);
    }
    if(mPosition.get_z() >= detectionSize ||mPosition.get_z() <= -detectionSize )
    {
        mPosition.set_z(detectionSize*mPosition.sign().get_z());
        set_velocity_after_bounce(3);
    }
}

void PhysicsObject::set_velocity_after_bounce(double direction)
{
    int x{1};
    int y{2};
    int z{3};
    double coefficientOfRestitution = mCoefficientOfRestitution;

    if (direction == x)
    {
        double velocityAfterBounce{-mVelocity.get_x()*coefficientOfRestitution};
        mVelocity.set_x(velocityAfterBounce);
    }
    else if (direction == y)
    {
        double velocityAfterBounce{-mVelocity.get_y()*coefficientOfRestitution};
        mVelocity.set_y(velocityAfterBounce);
    }
    else if (direction == z)
    {
        double velocityAfterBounce{-mVelocity.get_z()*coefficientOfRestitution};
        mVelocity.set_z(velocityAfterBounce);
    }
}

void PhysicsObject::create_sphere(Vector3 shapePosition, float sphereRadius, Vector3 initialVelocity)
{
    mRadius = sphereRadius;
    PhysicsObject sphere(shapePosition, initialVelocity, mGravity);
}

void PhysicsObject::move_back_from_wall(Vector3 directionOfMove)
{
    double detectionSize = mBoxSize-get_radius();
    Vector3 newPosition = directionOfMove*(-1*detectionSize);
    set_position(newPosition);
}

Vector3 PhysicsObject::sphere_collision(PhysicsObject object2)
{
    Vector3 position1 = get_position();
    Vector3 position2 = object2.get_position();
    Vector3 velocity1 = get_velocity();
    Vector3 velocity2 = object2.get_velocity();
    double cOfR1 = get_coefficient_of_restitution();
    double cOfR2 = object2.get_coefficient_of_restitution();
    double mass1 = get_mass();
    double mass2 = object2.get_mass();
    double velocity1MassRatio = (2*mass2/(mass1 + mass2));
    double velocity2MassRatio = (2*mass1/(mass1 + mass2));
    double positionMagnitude = (position1-position2).get_magnitude();
    double velocity1DotProduct = (velocity1-velocity2).dot(position1-position2);
    double velocity2DotProduct = (velocity2-velocity1).dot(position2-position1);

    Vector3 newVelocity1 = (velocity1 - (position1-position2)*velocity1MassRatio/(positionMagnitude*positionMagnitude)*velocity1DotProduct)*cOfR1;
    Vector3 newVelocity2 = (velocity2 - (position2-position1)*velocity2MassRatio/(positionMagnitude*positionMagnitude)*velocity2DotProduct)*cOfR2;
    set_velocity(newVelocity1);
    return newVelocity2;
}


void PhysicsObject::move_spheres_apart(PhysicsObject object2)
{
    Vector3 positionDifference = (get_position() - object2.get_position());
    double interferenceLimit = (get_radius() + object2.get_radius());
    double interferenceDistance = interferenceLimit - positionDifference.get_magnitude();

    if (interferenceDistance > 0)
    {
        Vector3 directionOfMove = positionDifference.normalize();
        Vector3 newPosition = directionOfMove*(interferenceDistance);
        set_position(get_position() + newPosition);
    }
}
