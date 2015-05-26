/************************************************
 * file  : math.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _MATH_H_
#define _MATH_H_

#include "../base/base.h"

NS_TINY3D_BEGIN

class math
{
public:
    static const float eplison;
    static const float pi;
    static const float deg2rad;
    static const float rad2deg;

public:
    template<typename T> static T clamp(T& t, const T& min, const T& max)
    {
        t = t > max ? max : t;
        t = t < min ? min : t;
        return t;
    }

    template<typename T> T static maximum(T& a, T& b)
    {
        return a > b ? a : b;
    }

    template<typename T> T static minimum(T& a, T& b)
    {
        return a < b ? a : b;
    }

    static int round(float value)
    {
        return (int)(value + 0.5f);
    }
};

NS_TINY3D_END

#endif//_MATH_H_