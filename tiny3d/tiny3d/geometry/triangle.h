/************************************************
 * file  : triangle.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "../base/base.h"
#include "../math/vector3.h"

NS_TINY3D_BEGIN

class triangle
{
public:
    triangle()
    {}

    triangle(const vector3& _p0, const vector3& _p1, const vector3& _p2)
        : p0(_p0), p1(_p1), p2(_p2)
    {}

public:
    vector3 p0;
    vector3 p1;
    vector3 p2;
};

NS_TINY3D_END

#endif//_TRIANGLE_H_