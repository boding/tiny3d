/************************************************
 * file  : vector2.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include "../base/base.h"
#include "math.h"
#include <math.h>

NS_TINY3D_BEGIN

class vector2
{
public:
    vector2() 
        : x(0), y(0)
    {}

    vector2(float _x, float _y)
        : x(_x), y(_y)
    {}

    inline float magnitude() const
    {
        return sqrt(x * x + y * y);
    }

    inline float sqrMagnitude() const
    {
        return x * x + y * y;
    }

    inline void normalize()
    {
        float magnitude = this->magnitude();
        if (magnitude < math::eplison)
        {
            *this = zero;
        }
        else
        {
            *this /= magnitude;
        }
    }

    inline vector2 normalized() const
    {
        vector2 v(*this);
        v.normalize();
        return v;
    }

    inline float distance(const vector2& other) const
    {
        return (*this - other).magnitude();
    }

    inline float sqrDistance(const vector2& other) const
    {
        return (*this - other).sqrMagnitude();
    }

    inline float dot(const vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    inline vector2 project(const vector2& other) const
    {
        return other * dot(other) / other.sqrMagnitude();
    }

    inline vector2 operator+(const vector2& other) const
    {
        return vector2(x + other.x, y + other.y);
    }

    inline vector2& operator+=(const vector2& other)
    {
        *this = *this + other;
        return *this;
    }

    inline vector2 operator-(const vector2& other) const
    {
        return vector2(x - other.x, y - other.y);
    }

    inline vector2& operator-=(const vector2& other)
    {
        *this = *this - other;
        return *this;
    }

    inline vector2 operator-()
    {
        return vector2(-x, -y);
    }

    inline vector2 operator*(float s) const
    {
        return vector2(x * s, y * s);
    }

    inline friend vector2 operator*(float s, const vector2& rhs)
    {
        return rhs * s;
    }

    inline vector2& operator*=(float s)
    {
        *this = *this * s;
        return *this;
    }

    inline vector2 operator/(float s) const
    {
        s = 1.f / s;
        return vector2(x * s, y * s);
    }

    inline vector2& operator/=(float s)
    {
        *this = *this / s;
        return *this;
    }

    inline bool operator==(const vector2& other)
    {
        return x == other.x && y == other.y;
    }

    inline bool operator!=(const vector2& other)
    {
        return !(*this == other);
    }

    inline static float dot(const vector2& a, const vector2& b)
    {
        return a.dot(b);
    }

    inline static vector2 project(const vector2& a, const vector2& b)
    {
        return a.project(b);
    }

    inline static vector2 reflect(const vector2& inDir, const vector2& inNormal)
    {
        return -2.f * inDir.project(inNormal) + inDir;
    }

    inline static float angle(const vector2& a, const vector2& b)
    {
        return acos(dot(a.normalized(), b.normalized())) * math::rad2deg;
    }

    inline static vector2 lerp(const vector2& a, const vector2& b, float t)
    {
        return a + (b - a) * t;
    }

public:
    static const vector2 one;
    static const vector2 zero;

public:
    float x;
    float y;
};

NS_TINY3D_END

#endif//_VECTOR2_H_