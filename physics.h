#ifndef PHYSICS_H
#define PHYSICS_H
#include "vector3d.h"
class Vector3;

class PhysicsObject
{
public:
    ~PhysicsObject();

    //Physics();
    double get_CoefficientOfRestitution() const;
    Vector3 get_position() const;
    Vector3 get_velocity() const;
    Vector3 get_acceleration() const;
    double get_drag_force() const;
    double get_mass() const;
    double get_radius() const;
    void update(double timestep); // increaments time, p,v,a; pass it dt. updates MPosition, etc.
    Vector3 box_collision(); // public?
    double mBoxSize{5};
//    Vector3 get_next_p();
//    Vector3 get_next_v();
//    Vector3 get_next_a();
//    double get_timestep();
//    Vector3 calculate_collision();

protected:

private:
    double mCoefficientOfRestitution{0.8};
    Vector3 mPosition{0,0,0};
    Vector3 mVelocity{0,0,0};
    Vector3 mAcceleration{0,0,0};
    double mDragForce{0};
    double mMass{0};
    double mRadius{0};


};
#endif // PHYSICS_H
