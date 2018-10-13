#include "gtest/gtest.h"
#include "vector3d.h"
#include "physicsObject.h"

void EXPECT_EQ_VECTORS(const Vector3& firstVector, const Vector3& secondVector)
{
    EXPECT_DOUBLE_EQ(firstVector.get_x(), secondVector.get_x());
    EXPECT_DOUBLE_EQ(firstVector.get_y(), secondVector.get_y());
    EXPECT_DOUBLE_EQ(firstVector.get_z(), secondVector.get_z());
}

void EXPECT_EQ_VECTORS_INT(const Vector3& firstVector, const Vector3& secondVector)
{
    EXPECT_EQ(firstVector.get_x(), secondVector.get_x());
    EXPECT_EQ(firstVector.get_y(), secondVector.get_y());
    EXPECT_EQ(firstVector.get_z(), secondVector.get_z());
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

TEST(Constructor,givenPhysicsValues_PhysicsPVAInitialized)
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

    Vector3 newPosition{0,0,-0.098};
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
    physicsObject.toggle_drag_force(turnOff);

    double timestep{0.1};
    physicsObject.update(timestep);
    physicsObject.update(timestep);

    Vector3 newPosition{0,0,-0.294};

    EXPECT_EQ_VECTORS(physicsObject.get_position(),newPosition);
}

TEST(Update,givenPhysicsObjectAtRestAndTenTimesteps_getUpdatedPosition)
{
    Vector3 position{0, 0, 0};
    Vector3 velocity{0, 0, 0};
    Vector3 gravity{0,0,-9.8};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);
    bool turnOff{0};
    physicsObject.toggle_drag_force(turnOff);

    double timestep{0.1};
    for(int i=0; i<10; i++)
    {
        physicsObject.update(timestep);
    }
    Vector3 newPosition{0,0,-5.39};

    EXPECT_EQ_VECTORS(physicsObject.get_position(),newPosition);
}

TEST(DragForce,givenPhysicsObject_getAccelerationAfterTenTimestep)
{
    PhysicsObject physicsObject;
    bool turnOn{1};
    physicsObject.toggle_drag_force(turnOn);
    double timestep{0.01};
    for(int i=0; i<10; i++)
    {
        physicsObject.update(timestep);
    }
    Vector3 calculatedAcceleration = physicsObject.calculate_drag_force();
    Vector3 expectedAcceleration{0,0,0.9462891031687630};
    EXPECT_EQ_VECTORS(expectedAcceleration,calculatedAcceleration);
}

TEST(MoveBack,givenSingleDirectionToMove_getNewPosition)
{
    Vector3 position{5, 0, 0};
    Vector3 velocity{0, 0, 0};
    Vector3 gravity{0,0,-9.8};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);
    Vector3 directionToMove{-1,0,0};

    physicsObject.move_back_from_wall(directionToMove);
    Vector3 expectedPosition{4,0,0};

    EXPECT_EQ_VECTORS(expectedPosition,physicsObject.get_position());
}

TEST(MoveBack,givenMultipleDirectionsToMove_getNewPosition)
{
    Vector3 position{5, 5, 0};
    Vector3 velocity{0, 0, 0};
    Vector3 gravity{0,0,-9.8};
    Vector3 acceleration = gravity;
    PhysicsObject physicsObject(position, velocity, acceleration);
    Vector3 directionToMove{-1,-1,0};

    physicsObject.move_back_from_wall(directionToMove);
    Vector3 expectedPosition{4.292893218813452,4.292893218813452,0};

    EXPECT_EQ_VECTORS(expectedPosition,physicsObject.get_position());
}

TEST(Gravity,givenTurnedOffGravity_getNewPosition)
{
    PhysicsObject physicsObject();
    ouble timestep{0.01};
    for(int i=0; i<10; i++)
    {
        physicsObject.update(timestep);
    }

}





// turn off gravity
// box collision without gravity
// make test fixture
