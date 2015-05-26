/************************************************
 * file  : line.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _LINE_H_
#define _LINE_H_

#include "../base/base.h"
#include "../math/vector3.h"

NS_TINY3D_BEGIN

class line
{
public:
    line()
    {}

    line(const vector3& _p0, const vector3& _p1)
        : p0(_p0), p1(_p1)
    {}

public:
    vector3 p0;
    vector3 p1;
};

NS_TINY3D_END

#endif//_LINE_H_