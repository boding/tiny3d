/************************************************
 * file  : plane.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _PLANE_H_
#define _PLANE_H_

#include "../base/base.h"
#include "../math/vector3.h"

NS_TINY3D_BEGIN

class plane
{
public:
    vector3 n;
    vector3 p;
};

NS_TINY3D_END

#endif//_PLANE_H_