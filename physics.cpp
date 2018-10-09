#include "physics.h"
#include "vector3d.h"

Physics::~Physics()
{
}

//Physics::Physics(Vector3 p, Vector3 v, Vector3 a):mPosition{0,0,0}, mVelocity{0,0,0}, mAcceleration{0,0,0}
//{

//}

double Physics::get_CoefficientOfRestitution() const
{
    return mCoefficientOfRestitution;
}

Vector3 Physics::get_p() const
{
    return mPosition;
}

Vector3 Physics::get_v() const
{
    return mVelocity;
}

Vector3 Physics::get_a() const
{
    return mAcceleration;
}

double Physics::get_drag_force() const
{
    double dragForce{0};
    //dragForce = (1/2)*density*(get_v()*get_v())*get_CoefficientOfRestitution()*get_radius();
    return dragForce;
}

double Physics::get_mass() const
{
    return mMass;
}

//Vector3 get_next_p()
//{
//    Vector3 next_p = get_p() + get_next_v()*get_timestep();
//    return next_p;
//}

//Vector3 get_next_v()
//{
//    Vector3 next_v = get_v() + get_next_a()*get_timestep();
//    return next_v;
//}

//Vector3 get_next_a()
//{
//    Vector3 next_a = get_a() + get_drag_force()/get_mass();
//    return next_a;
//}

//double get_timestep()
//{
//    double timestep{0.1};
//    return timestep;
//}

//Vector3 calculate_collision()
//{
//    Vector3 next_v = -get_CoefficientOfRestitution()*get_v;
//    return next_v;
//}



