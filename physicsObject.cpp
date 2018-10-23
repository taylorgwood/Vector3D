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

void PhysicsObject::enable_drag_force(bool On)
{
    mDragForceOn = On;
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

double PhysicsObject::get_box_size() const
{
    return mBoxSize;
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
//    sphere_collision_loop();
}

void PhysicsObject::box_collision()
{
    double boxSize = mBoxSize;
    double x{1};
    double y{2};
    double z{3};

    double detectionSize = boxSize-get_radius();
    if (which_wall_is_sphere_against(this).get_x() == 1)
    {
        mPosition.set_x(detectionSize*mPosition.sign().get_x());
        set_velocity_after_bounce(x);
    }
    if (which_wall_is_sphere_against(this).get_y() == 1)
    {
        mPosition.set_y(detectionSize*mPosition.sign().get_y());
        set_velocity_after_bounce(y);
    }
    if (which_wall_is_sphere_against(this).get_z() == 1)
    {
        mPosition.set_z(detectionSize*mPosition.sign().get_z());
        set_velocity_after_bounce(z);
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

void PhysicsObject::sphere_collision(PhysicsObject* objectToCompare)
{
    if (objectToCompare != this)
    {
        set_new_sphere_velocities(objectToCompare);
        move_spheres_apart(objectToCompare);
    }
}

void PhysicsObject::set_new_sphere_velocities(PhysicsObject* object2)
{   
    Vector3 position1 = this->get_position();
    Vector3 position2 = object2->get_position();
    Vector3 velocity1 = this->get_velocity();
    Vector3 velocity2 = object2->get_velocity();
    double cOfR1 = get_coefficient_of_restitution();
    double cOfR2 = object2->get_coefficient_of_restitution();
    double mass1 = get_mass();
    double mass2 = object2->get_mass();
    double velocity1MassRatio = (2*mass2/(mass1 + mass2));
    double velocity2MassRatio = (2*mass1/(mass1 + mass2));
    double positionMagnitude = (position1-position2).get_magnitude();
    double velocity1DotProduct = (velocity1-velocity2).dot(position1-position2);
    double velocity2DotProduct = (velocity2-velocity1).dot(position2-position1);

    Vector3 newVelocity1 = (velocity1 - (position1-position2)*velocity1MassRatio/(positionMagnitude*positionMagnitude)*velocity1DotProduct)*cOfR1;
    Vector3 newVelocity2 = (velocity2 - (position2-position1)*velocity2MassRatio/(positionMagnitude*positionMagnitude)*velocity2DotProduct)*cOfR2;
    if (this->is_against_wall(this))
    {
        Vector3 wallAgainst = this->which_wall_is_sphere_against(this);
        double onWall{1};
        if (wallAgainst.get_x() == onWall)
        {
            newVelocity2.set_x(velocity2.get_x()*(-cOfR1*cOfR2));
            newVelocity1.set_x(velocity1.get_x());
        }
        if (wallAgainst.get_y() == onWall)
        {
            newVelocity2.set_y(velocity2.get_y()*(-cOfR1*cOfR2));
            newVelocity1.set_y(velocity1.get_y());
        }
        if (wallAgainst.get_z() == onWall)
        {
            newVelocity2.set_z(velocity2.get_z()*(-cOfR1*cOfR2));
            newVelocity1.set_z(velocity1.get_z());
        }
    }
    if (object2->is_against_wall(object2))
    {
        Vector3 wallAgainst = object2->which_wall_is_sphere_against(object2);
        double onWall{1};
        if (wallAgainst.get_x() == onWall)
        {
            newVelocity1.set_x(velocity1.get_x()*(-cOfR1*cOfR2));
            newVelocity2.set_x(velocity2.get_x());
        }
        if (wallAgainst.get_y() == onWall)
        {
            newVelocity1.set_y(velocity1.get_y()*(-cOfR1*cOfR2));
            newVelocity2.set_y(velocity2.get_y());
        }
        if (wallAgainst.get_z() == onWall)
        {
            newVelocity1.set_z(velocity1.get_z()*(-cOfR1*cOfR2));
            newVelocity2.set_z(velocity2.get_z());
        }
    }
    this->set_velocity(newVelocity1);
    object2->set_velocity(newVelocity2);
}

void PhysicsObject::move_spheres_apart(PhysicsObject *object2)
{
    Vector3 positionDifference = (get_position() - object2->get_position());
    double interferenceLimit = (get_radius() + object2->get_radius());
    double interferenceDistance = interferenceLimit - positionDifference.get_magnitude();

    if (interferenceDistance > 0)
    {
        Vector3 directionOfMove = positionDifference.normalize();
        Vector3 moveDistance = directionOfMove*(interferenceDistance);
        Vector3 newPosition1 = get_position() + moveDistance;
        Vector3 currentPosition1 = get_position();
        Vector3 currentPosition2 = object2->get_position();
        this->set_position(newPosition1);
        if (is_against_wall(this))
        {
            this->set_position(currentPosition1);
        }
    }
}

double PhysicsObject::get_sphere_collision_distance(PhysicsObject object2)
{
    Vector3 positionDifference = (get_position() - object2.get_position());
    double interferenceLimit = (get_radius() + object2.get_radius());
    double interferenceDistance = interferenceLimit - positionDifference.get_magnitude();
    return interferenceDistance;
}

bool PhysicsObject::are_spheres_collided(PhysicsObject object2)
{
    double interferenceDistance = get_sphere_collision_distance(object2);
    bool areCollided{false};
    if (interferenceDistance > 0)
    {
        areCollided = true;
    }
    return areCollided;
}

void PhysicsObject::sphere_collision_loop()
{
    if (mObjectList != nullptr)
    {
        int numberOfSpheres = mObjectList->size();
        for (int i=0; i<numberOfSpheres; i++)
        {
            PhysicsObject* object2 = mObjectList->at(i);
            sphere_collision(object2);
        }
    }
}

Vector3 PhysicsObject::which_wall_is_sphere_against(PhysicsObject* object)
{
    Vector3 against_wall{0,0,0};
    double buffer{0.001};
    double detectionSize = object->get_box_size()-object->get_radius()-buffer;
    if (object->get_position().get_x() >= detectionSize || object->get_position().get_x() <= -detectionSize)
    {
        against_wall.set_x(1);
    }
    if(object->get_position().get_y() >= detectionSize || object->get_position().get_y() <= -detectionSize)
    {
        against_wall.set_y(1);
    }
    if(object->get_position().get_z() >= detectionSize ||object->get_position().get_z() <= -detectionSize )
    {
        against_wall.set_z(1);
    }
    return against_wall;
}

bool PhysicsObject::is_against_wall(PhysicsObject* object)
{
    bool againstWall{false};
    if (which_wall_is_sphere_against(object).get_magnitude() > 0)
    {
        againstWall = true;
    }
    return againstWall;
}

void PhysicsObject::pass_in_object_list(std::vector<PhysicsObject*> *objectList)
{
    if (mObjectList != nullptr && mObjectList != objectList)
        delete mObjectList;

    mObjectList = objectList;
}
