/************************************************
 * file  : cube.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _CUBE_H_
#define _CUBE_H_

#include "../base/base.h"
#include "../math/vector3.h"

NS_TINY3D_BEGIN

class cube
{
public:
    cube(const vector3 pivot, float size)
    {
        v[0] = pivot + vector3(-size, -size, -size);
        v[1] = pivot + vector3( size, -size, -size);
        v[2] = pivot + vector3( size,  size, -size);
        v[3] = pivot + vector3(-size,  size, -size);

        v[4] = pivot + vector3(-size, -size,  size);
        v[5] = pivot + vector3( size, -size,  size);
        v[6] = pivot + vector3( size,  size,  size);
        v[7] = pivot + vector3(-size,  size,  size);
    }

public:
    vector3 v[8];
};

NS_TINY3D_END

#endif