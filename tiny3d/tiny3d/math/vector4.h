/************************************************
 * file  : vector4.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include "../base/base.h"
#include "math.h"
#include <math.h>

NS_TINY3D_BEGIN

class vector4
{
public:
    vector4() 
        : x(0), y(0), z(0), w(0)
    {}

    vector4(float _x, float _y, float _z, float _w)
        : x(_x), y(_y), z(_z), w(_w)
    {}

    inline float magnitude() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    inline float sqrMagnitude() const
    {
        return x * x + y * y + z * z + w * w;
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

    inline vector4 normalized() const
    {
        vector4 v(*this);
        v.normalize();
        return v;
    }

    inline float distance(const vector4& other) const
    {
        return (*this - other).magnitude();
    }

    inline float sqrDistance(const vector4& other) const
    {
        return (*this - other).sqrMagnitude();
    }

    inline float dot(const vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    inline vector4 project(const vector4& other) const
    {
        return other * dot(other) / other.sqrMagnitude();
    }

    inline vector4 operator+(const vector4& other) const
    {
        return vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    inline vector4& operator+=(const vector4& other)
    {
        *this = *this + other;
        return *this;
    }

    inline vector4 operator-(const vector4& other) const
    {
        return vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    inline vector4& operator-=(const vector4& other)
    {
        *this = *this - other;
        return *this;
    }

    inline vector4 operator-()
    {
        return vector4(-x, -y, -z, -w);
    }

    inline vector4 operator*(float s) const
    {
        return vector4(x * s, y * s, z * s, w * s);
    }

    inline friend vector4 operator*(float s, const vector4& rhs)
    {
        return rhs * s;
    }

    inline vector4& operator*=(float s)
    {
        *this = *this * s;
        return *this;
    }

    inline vector4 operator/(float s) const
    {
        s = 1.f / s;
        return vector4(x * s, y * s, z * s, w * s);
    }

    inline vector4& operator/=(float s)
    {
        *this = *this / s;
        return *this;
    }

    inline bool operator==(const vector4& other)
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    inline bool operator!=(const vector4& other)
    {
        return !(*this == other);
    }

    inline static float dot(const vector4& a, const vector4& b)
    {
        return a.dot(b);
    }

    inline static vector4 project(const vector4& a, const vector4& b)
    {
        return a.project(b);
    }

    inline static vector4 lerp(const vector4& a, const vector4& b, float t)
    {
        return a + (b - a) * t;
    }

public:
    static const vector4 one;
    static const vector4 zero;

public:
    float x;
    float y;
    float z;
    float w;
};

NS_TINY3D_END

#endif//_VECTOR4_H_