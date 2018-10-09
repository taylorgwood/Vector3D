#ifndef PHYSICS_H
#define PHYSICS_H
#include "vector3d.h"
class Vector3;

class Physics
{
public:
    ~Physics();

    //Physics();
    double get_CoefficientOfRestitution() const;
    Vector3 get_p() const;
    Vector3 get_v() const;
    Vector3 get_a() const;
    double get_drag_force() const;
    double get_mass() const;
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


};
#endif // PHYSICS_H
