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

TEST(Update,givenPhysicsObjectAndTimestep_getUpdatedPhysicsObject)
{
    Vector3 position{0, 0, 0};
    Vector3 velocity{0, 0, 0};
    Vector3 acceleration{0, 0, 0};
    PhysicsObject physicsObject(position, velocity, acceleration);

    EXPECT_EQ_VECTORS(physicsObject.get_position(),position);
    EXPECT_EQ_VECTORS(physicsObject.get_velocity(),velocity);
    EXPECT_EQ_VECTORS(physicsObject.get_acceleration(),acceleration);
}
