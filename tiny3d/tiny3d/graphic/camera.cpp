/************************************************
 * file  : camera.cpp
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#include "camera.h"

NS_TINY3D_BEGIN

void camera::apply()
{
    // world to camera
    matrix4 t(matrix4::identify), r(matrix4::identify);
    t.m30 = position.x;
    t.m31 = position.y;
    t.m32 = position.z;
    r = matrix4::rotation(rotation);
    wc = t.inversed() * r.inversed();
}

vector3 camera::world2view(const vector3& world) const
{
    vector3 v = world * wc;

    v.x = (float)width * 0.5f * v.x / v.z;
    v.y = (float)height * 0.5f * v.y * aspect / v.z;

    return v;
}

NS_TINY3D_END