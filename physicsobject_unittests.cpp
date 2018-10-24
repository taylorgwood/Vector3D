#include <iostream>
#include "gtest/gtest.h"
#include "vector3d.h"
#include "physicsObject.h"

void EXPECT_EQ_VECTORS(const Vector3& firstVector, const Vector3& secondVector)
{
    EXPECT_DOUBLE_EQ(firstVector.get_x(), secondVector.get_x());
    EXPECT_DOUBLE_EQ(firstVector.get_y(), secondVector.get_y());
    EXPECT_DOUBLE_EQ(firstVector.get_z(), secondVector.get_z());
}

TEST(Constructor,setNoValues_getZeroVector)
{
    PhysicsObject physicsObject;
    Vector3 positionOutput = physicsObject.get_position();
    Vector3 emptyPosition{0,0,0};
    EXPECT_EQ_VECTORS(emptyPosition,positionOutput);
}

TEST(PositionGetterSetter,setPhysicsPosition_getCorrectPositionBack)
{
    PhysicsObject physicsObject;
    Vector3 positionInput{1,2,3};
    physicsObject.set_position(positionInput);
    Vector3 positionOutput = physicsObject.get_position();
    EXPECT_EQ_VECTORS(positionInput,positionOutput);
}

TEST(Constructor,givenPhysicsValues_getPhysicsPVAInitialized)
{
    Vector3 position{1, 2, 3};
    Vector3 velocity{6, 5, 4};
    Vector3 acceleration{0, 9.8, 9.8};
    PhysicsObject physicsObject(position, velocity, acceleration);

    EXPECT_EQ_VECTORS(physicsObject.get_position(),position);
    EXPECT_EQ_VECTORS(physicsObject.get_velocity(),velocity);
    EXPECT_EQ_VECTORS(physicsObject.get_acceleration(),acceleration);
}

TEST(Update,givenPhysicsObjectAtRestAndTimestep_getUpdatedPosition)
{
    Vector3 position{0, 0, 0};
    Vector3 velocity{0, 0, 0};
    Vector3 gravity{0,0,-9.8};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);

    double timestep{0.1};
    physicsObject.update(timestep);

    Vector3 newPosition{0,0,0};
    Vector3 newVelocity{0,0,-0.98};
    Vector3 newAcceleration{0,0,-9.8};

    EXPECT_EQ_VECTORS(physicsObject.get_position(),newPosition);
}

TEST(Update,givenPhysicsObjectAtRestAndTwoTimesteps_getUpdatedPosition)
{
    Vector3 position{0, 0, 0};
    Vector3 velocity{0, 0, 0};
    Vector3 gravity{0,0,-9.8};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);
    bool turnOff{0};
    physicsObject.enable_drag_force(turnOff);

    double timestep{0.1};
    physicsObject.update(timestep);
    physicsObject.update(timestep);

    Vector3 newPosition{0,0,-0.098};

    EXPECT_EQ_VECTORS(physicsObject.get_position(),newPosition);
}

TEST(DragForce,givenPhysicsObject_getDragAfterFourTimestep)
{
    PhysicsObject physicsObject;
    bool turnOn{1};
    physicsObject.enable_drag_force(turnOn);
    double timestep{0.01};
    for(int i=0; i<4; i++)
    {
        physicsObject.update(timestep);
    }
    double calculatedDrag = physicsObject.calculate_drag_force().get_z();
    double expectedDrag{0.153839};
    EXPECT_NEAR(expectedDrag,calculatedDrag, 0.00001);
}

TEST(DragForce,givenPhysicsObject_getAccelerationAfterTenTimestep)
{
    PhysicsObject physicsObject;
    bool turnOn{1};
    physicsObject.enable_drag_force(turnOn);
    double timestep{0.01};
    for(int i=0; i<10; i++)
    {
        physicsObject.update(timestep);
    }
    double calculatedAcceleration = physicsObject.get_acceleration().get_z();
    double expectedAcceleartion{-9.72234};
    EXPECT_NEAR(expectedAcceleartion,calculatedAcceleration, 0.0001);
}

TEST(MoveBack,givenNegativeDirectionToMove_getNewPosition)
{
    Vector3 position{0, 0, 5};
    Vector3 velocity{0, 0, 0};
    Vector3 gravity{0,0,-9.8};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);
    Vector3 directionToMove{0,0,-1};

    physicsObject.move_back_from_wall(directionToMove);
    Vector3 expectedPosition{0,0,4};

    EXPECT_EQ_VECTORS(expectedPosition,physicsObject.get_position());
}

TEST(MoveBack,givenPositiveDirectionToMove_getNewPosition)
{
    Vector3 position{-5, 0, 0};
    Vector3 velocity{0, 0, 0};
    Vector3 gravity{0,0,-9.8};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);
    Vector3 directionToMove{1,0,0};

    physicsObject.move_back_from_wall(directionToMove);
    Vector3 expectedPosition{-4,0,0};

    EXPECT_EQ_VECTORS(expectedPosition,physicsObject.get_position());
}

TEST(MoveBack,givenMultipleDirectionsToMove_getNewPosition)
{
    Vector3 position{5, 0, 0};
    Vector3 velocity{5, 0, 0};
    Vector3 gravity{0,0,-9.8};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);
    float sphereRadius = 1.0;
    physicsObject.create_sphere(position,sphereRadius,velocity);
    Vector3 directionToMove{-1,-1,0};

    physicsObject.move_back_from_wall(directionToMove);
    Vector3 expectedPosition{4,4,0};

    EXPECT_EQ_VECTORS(expectedPosition,physicsObject.get_position());
}

TEST(WallBounce,givenXVelocityTowardWallNoGravity_getNegativeVelocity)
{
    Vector3 position{5, 0, 0};
    Vector3 velocity{10, 0, 0};
    Vector3 gravity{0, 0, 0};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);

    physicsObject.box_collision();
    Vector3 expectedVelocity{-8,0,0};

    EXPECT_EQ_VECTORS(expectedVelocity, physicsObject.get_velocity());
}

TEST(WallBounce,givenZVelocityTowardWallNoGravity_getNegativeVelocity)
{
    Vector3 position{0, 0, 5};
    Vector3 velocity{0, 0, 10};
    Vector3 gravity{0, 0, 0};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);

    physicsObject.box_collision();
    Vector3 expectedVelocity{0,0,-8};

    EXPECT_EQ_VECTORS(expectedVelocity, physicsObject.get_velocity());
}

TEST(WallBounce,givenXYZVelocityTowardWallNoGravity_getNegativeVelocity)
{
    Vector3 position{5, -5, 5};
    Vector3 velocity{1, -20, 1};
    Vector3 gravity{0, 0, 0};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);

    physicsObject.box_collision();
    Vector3 expectedVelocity{-0.8,16,-0.8};

    EXPECT_EQ_VECTORS(expectedVelocity, physicsObject.get_velocity());
}

TEST(WallBounce,givenZVelocityAtWallNoGravity_getCorrectLocation)
{
    Vector3 position{0, 0, 5};
    Vector3 velocity{0, 0, 10};
    Vector3 gravity{0, 0, 0};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);
    float sphereRadius = 0.5;
    physicsObject.create_sphere(position,sphereRadius,velocity);

    physicsObject.box_collision();
    Vector3 expectedPosition{0,0,4.5};

    EXPECT_EQ_VECTORS(expectedPosition, physicsObject.get_position());
}

TEST(WallBounce,givenYVelocityAtWallNoDrag_getCorrectLocationAfterTwoTimesteps)
{
    Vector3 position{0, -3.65, 0};
    Vector3 velocity{0, -1, 0};
    Vector3 gravity{0, 0, 0};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);
    float sphereRadius = 1.0;
    physicsObject.create_sphere(position,sphereRadius,velocity);
    physicsObject.reset_gravity(gravity);
    bool turnOff{0};
    physicsObject.enable_drag_force(turnOff);

    double timestep{0.1};
    for(int i=0; i<10; i++)
    {
        physicsObject.update(timestep);
    }
    double expectedPosition{-3.52};

    EXPECT_DOUBLE_EQ(expectedPosition, physicsObject.get_position().get_y());
}

TEST(SphereCollision,givenTwoIdenticalSpheres_getCorrectVelocities)
{
    Vector3 position1{0, 0, 0};
    Vector3 position2{1, 0, 0};
    Vector3 velocity1{1, 0, 0};
    Vector3 velocity2{-1, 0, 0};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR,fluidDensity);

    object1->sphere_collision(object2);
    Vector3 calculatedVelocity1 = object1->get_velocity();
    Vector3 calculatedVelocity2 = object2->get_velocity();
    Vector3 expectedVelocity1{-0.8,0,0};
    Vector3 expectedVelocity2{0.8,0,0};

    EXPECT_EQ_VECTORS(expectedVelocity1,calculatedVelocity1);
    EXPECT_EQ_VECTORS(expectedVelocity2,calculatedVelocity2);
}

TEST(SphereCollision,givenTwoSpheres_getCorrectVelocities)
{
    Vector3 position1{0, 0, 0};
    Vector3 position2{1, 0, 0};
    Vector3 velocity1{1, 0, 0};
    Vector3 velocity2{-1, 0, 0};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass1{1};
    double mass2{2};
    double cOfR{1.0};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass1,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass2,cOfR,fluidDensity);

    object1->sphere_collision(object2);
    double calculatedVelocity1 = object1->get_velocity().get_x();
    double calculatedVelocity2 = object2->get_velocity().get_x();
    double expectedVelocity1{-1.6666};
    double expectedVelocity2{0.33333};

    EXPECT_NEAR(expectedVelocity1,calculatedVelocity1,0.0001);
    EXPECT_NEAR(expectedVelocity2,calculatedVelocity2,0.0001);
}

TEST(SeperateSpheres,givenTwoSpheresCollided_getCorrectPosition)
{
    Vector3 position1{2, 0, 0};
    Vector3 position2{0.25, 0, 0};
    Vector3 velocity{1, 0, 0};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity,gravity,radius,mass,cOfR,fluidDensity);

    object1->move_spheres_apart(object2);
    Vector3 calculatedPosition1 = object1->get_position();
    Vector3 calculatedPosition2 = object2->get_position();
    Vector3 expectedPosition1{2.25, 0, 0};
    Vector3 expectedPosition2{0.25, 0, 0};

    EXPECT_EQ_VECTORS(expectedPosition1,calculatedPosition1);
    EXPECT_EQ_VECTORS(expectedPosition2,calculatedPosition2);
}

TEST(SeperateSpheres,givenTwoSpheresApart_getCorrectPosition)
{
    Vector3 position1{3, 0, 0};
    Vector3 position2{0.25, 0, 0};
    Vector3 velocity{1, 0, 0};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity,gravity,radius,mass,cOfR,fluidDensity);

    object1->move_spheres_apart(object2);
    Vector3 calculatedPosition1 = object1->get_position();
    Vector3 calculatedPosition2 = object2->get_position();
    Vector3 expectedPosition1{3, 0, 0};
    Vector3 expectedPosition2{0.25, 0, 0};

    EXPECT_EQ_VECTORS(expectedPosition1,calculatedPosition1);
    EXPECT_EQ_VECTORS(expectedPosition2,calculatedPosition2);
}

TEST(SeperateSpheres,givenTwoSpheresCollidedAcrossZero_getCorrectPosition)
{
    Vector3 position1{1.5, 0, 0};
    Vector3 position2{-0.25, 0, 0};
    Vector3 velocity{1, 0, 0};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity,gravity,radius,mass,cOfR,fluidDensity);

    object1->move_spheres_apart(object2);
    Vector3 calculatedPosition1 = object1->get_position();
    Vector3 calculatedPosition2 = object2->get_position();
    Vector3 expectedPosition1{1.75, 0, 0};
    Vector3 expectedPosition2{-0.25, 0, 0};

    EXPECT_EQ_VECTORS(expectedPosition1,calculatedPosition1);
    EXPECT_EQ_VECTORS(expectedPosition2,calculatedPosition2);
}

TEST(SphereCollision,givenTwoSpheresSecondIsAgainstWall_getCorrectPositions)
{
    Vector3 position1{0, 0, -2.25};
    Vector3 position2{0, 0, -4};
    Vector3 velocity1{0, 0, 0};
    Vector3 velocity2{0, 0, -1};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR,fluidDensity);

    object1->sphere_collision(object2);
    Vector3 calculatedPosition1 = object1->get_position();
    Vector3 calculatedPosition2 = object2->get_position();
    Vector3 expectedPosition1{0, 0, -2};
    Vector3 expectedPosition2{0, 0, -4};

    EXPECT_EQ_VECTORS(expectedPosition1,calculatedPosition1);
    EXPECT_EQ_VECTORS(expectedPosition2,calculatedPosition2);
}

TEST(SphereCollision,givenTwoSpheresApart_getCorrectPositions)
{
    Vector3 position1{0, 0, -2};
    Vector3 position2{0, 0, 2};
    Vector3 velocity1{0, 0, 0};
    Vector3 velocity2{0, 0, -1};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR,fluidDensity);

    object1->sphere_collision(object2);
    Vector3 calculatedPosition1 = object1->get_position();
    Vector3 calculatedPosition2 = object2->get_position();
    Vector3 expectedPosition1{0, 0, -2};
    Vector3 expectedPosition2{0, 0, 2};

    EXPECT_EQ_VECTORS(expectedPosition1,calculatedPosition1);
    EXPECT_EQ_VECTORS(expectedPosition2,calculatedPosition2);
}

TEST(SphereCollision,givenTwoSpheresCollided_getCorrectVelocities)
{
    Vector3 position1{0, 0, -1};
    Vector3 position2{0, 0, 1};
    Vector3 velocity1{0, 0, 1};
    Vector3 velocity2{0, 0, -1};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR,fluidDensity);

    object1->sphere_collision(object2);
    Vector3 calculatedVelocity1 = object1->get_velocity();
    Vector3 calculatedVelocity2 = object2->get_velocity();
    Vector3 expectedVelocity1{0, 0, -0.8};
    Vector3 expectedVelocity2{0, 0, 0.8};

    EXPECT_EQ_VECTORS(expectedVelocity1,calculatedVelocity1);
    EXPECT_EQ_VECTORS(expectedVelocity2,calculatedVelocity2);
}

TEST(SphereCollision,givenTwoSpheresFirstIsAgainstWall_getCorrectPositions)
{
    Vector3 position1{0, 0, -4};
    Vector3 position2{0, 0, -2.25};
    Vector3 velocity1{0, 0, 0};
    Vector3 velocity2{0, 0, -1};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR,fluidDensity);

    object1->sphere_collision(object2);
    Vector3 calculatedPosition1 = object1->get_position();
    Vector3 calculatedPosition2 = object2->get_position();
    Vector3 expectedPosition1{0, 0, -4};
    Vector3 expectedPosition2{0, 0, -2.25};

    EXPECT_EQ_VECTORS(expectedPosition1,calculatedPosition1);
    EXPECT_EQ_VECTORS(expectedPosition2,calculatedPosition2);
}

TEST(AgainstWall,givenFirstSphereAgainstWall_getAgainstWallFlag)
{
    Vector3 position1{0, 0, -4};
    Vector3 velocity1{0, 0, 0};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR,fluidDensity);

    bool isAgainstWall = object1->is_against_wall(object1);

    EXPECT_TRUE(isAgainstWall);
}

TEST(AgainstWall,givenSecondSphereAgainstWall_getAgainstWallFlag)
{
    Vector3 position1{0, 0, 0};
    Vector3 velocity1{0, 0, 0};
    Vector3 position2{0, 0, 4};
    Vector3 velocity2{0, 0, 0};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR,fluidDensity);

    bool isAgainstWall1 = object1->is_against_wall(object1);
    bool isAgainstWall2 = object2->is_against_wall(object2);

    EXPECT_FALSE(isAgainstWall1);
    EXPECT_TRUE(isAgainstWall2);
}

TEST(SphereCollision,givenTwoSpheresFirstAgainstWall_getCorrectVelocities)
{
    Vector3 position1{0, 0, -4};
    Vector3 position2{0, 0, -2.25};
    Vector3 velocity1{0, 0, 0};
    Vector3 velocity2{0, 0, -1};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR1{0.8};
    double cOfR2{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR1,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR2,fluidDensity);

    object1->sphere_collision(object2);
    Vector3 calculatedVelocity1 = object1->get_velocity();
    Vector3 calculatedVelocity2 = object2->get_velocity();
    double newVelocityInZDirection{0.64};
    Vector3 expectedVelocity1{0, 0, 0};
    Vector3 expectedVelocity2{0, 0, newVelocityInZDirection};

    EXPECT_EQ_VECTORS(expectedVelocity1,calculatedVelocity1);
    EXPECT_EQ_VECTORS(expectedVelocity2,calculatedVelocity2);
}

TEST(SphereCollision,givenTwoSpheresSecondAgainstWall_getCorrectVelocities)
{
    Vector3 position1{0, 0, -2.25};
    Vector3 position2{0, 0, -4};
    Vector3 velocity1{0, 0, -1};
    Vector3 velocity2{0, 0, 0};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR1{0.8};
    double cOfR2{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR1,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR2,fluidDensity);

    object1->sphere_collision(object2);
    Vector3 calculatedVelocity1 = object1->get_velocity();
    Vector3 calculatedVelocity2 = object2->get_velocity();
    double newVelocity1InZDirection{0.64};
    Vector3 expectedVelocity1{0, 0, newVelocity1InZDirection};
    Vector3 expectedVelocity2{0, 0, 0};

    EXPECT_EQ_VECTORS(expectedVelocity1,calculatedVelocity1);
    EXPECT_EQ_VECTORS(expectedVelocity2,calculatedVelocity2);
}

TEST(SphereCollision,givenTwoSpheresSecondAgainstWallFirstWithYZVelocity_getCorrectVelocities)
{
    Vector3 position1{0, 0, -2.25};
    Vector3 position2{0, 0, -4};
    Vector3 velocity1{0, -1, -1};
    Vector3 velocity2{0, 0, 0};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR1{0.8};
    double cOfR2{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR1,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR2,fluidDensity);

    object1->sphere_collision(object2);
    Vector3 calculatedVelocity1 = object1->get_velocity();
    Vector3 calculatedVelocity2 = object2->get_velocity();
    double newVelocity1InYDirection{-0.8};
    double newVelocity1InZDirection{0.64};
    Vector3 expectedVelocity1{0, newVelocity1InYDirection, newVelocity1InZDirection};
    Vector3 expectedVelocity2{0, 0, 0};

    EXPECT_EQ_VECTORS(expectedVelocity1,calculatedVelocity1);
    EXPECT_EQ_VECTORS(expectedVelocity2,calculatedVelocity2);
}

TEST(SphereCollision,givenTwoSpheresFirstAgainstWallFirstWithXYZVelocity_getCorrectVelocities)
{
    Vector3 position1{0, 0, 4};
    Vector3 position2{0, 0, 2.25};
    Vector3 velocity1{0, 0, 0};
    Vector3 velocity2{1, 1, 1};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR1{0.8};
    double cOfR2{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR1,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR2,fluidDensity);

    object1->sphere_collision(object2);
    Vector3 calculatedVelocity1 = object1->get_velocity();
    Vector3 calculatedVelocity2 = object2->get_velocity();
    double newVelocity2InXDirection{0.8};
    double newVelocity2InYDirection{0.8};
    double newVelocity2InZDirection{-0.64};
    Vector3 expectedVelocity1{0, 0, 0};
    Vector3 expectedVelocity2{newVelocity2InXDirection, newVelocity2InYDirection, newVelocity2InZDirection};

    EXPECT_EQ_VECTORS(expectedVelocity1,calculatedVelocity1);
    EXPECT_EQ_VECTORS(expectedVelocity2,calculatedVelocity2);
}

TEST(SphereCollision,givenObjectList_getCorrectVelocitiesAfterCollision)
{
    Vector3 position1{0, 0, -1};
    Vector3 position2{0, 0, 1};
    Vector3 velocity1{0, 0, 1};
    Vector3 velocity2{0, 0, -1};
    Vector3 gravity{0, 0, 0};
    float radius{1};
    double mass{1};
    double cOfR{0.8};
    double fluidDensity{0};

    PhysicsObject* object1 = new PhysicsObject(position1,velocity1,gravity,radius,mass,cOfR,fluidDensity);
    PhysicsObject* object2 = new PhysicsObject(position2,velocity2,gravity,radius,mass,cOfR,fluidDensity);

    std::vector<PhysicsObject*> *objectList = new std::vector<PhysicsObject*>;
    objectList->push_back(object1);
    objectList->push_back(object2);
    object1->pass_in_object_list(objectList);
    object1->sphere_collision_loop();
    Vector3 calculatedVelocity1 = object1->get_velocity();
    Vector3 calculatedVelocity2 = object2->get_velocity();
    Vector3 expectedVelocity1{0, 0, -0.8};
    Vector3 expectedVelocity2{0, 0, 0.8};

    EXPECT_EQ_VECTORS(expectedVelocity1,calculatedVelocity1);
    EXPECT_EQ_VECTORS(expectedVelocity2,calculatedVelocity2);
}
