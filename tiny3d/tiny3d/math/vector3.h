/************************************************
 * file  : vector3.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "../base/base.h"
#include "math.h"
#include <math.h>

NS_TINY3D_BEGIN

class vector3
{
public:
    vector3() 
        : x(0), y(0), z(0)
    {}

    vector3(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
    {}

    inline float magnitude() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    inline float sqrMagnitude() const
    {
        return x * x + y * y + z * z;
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

    inline vector3 normalized() const
    {
        vector3 v(*this);
        v.normalize();
        return v;
    }

    inline float distance(const vector3& other) const
    {
        return (*this - other).magnitude();
    }

    inline float sqrDistance(const vector3& other) const
    {
        return (*this - other).sqrMagnitude();
    }

    inline float dot(const vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    inline vector3 cross(const vector3& other) const
    {
        return vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
            );
    }

    inline vector3 project(const vector3& other) const
    {
        return other * dot(other) / other.sqrMagnitude();
    }

    inline vector3 operator+(const vector3& other) const
    {
        return vector3(x + other.x, y + other.y, z + other.z);
    }

    inline vector3& operator+=(const vector3& other)
    {
        *this = *this + other;
        return *this;
    }

    inline vector3 operator-(const vector3& other) const
    {
        return vector3(x - other.x, y - other.y, z - other.z);
    }

    inline vector3& operator-=(const vector3& other)
    {
        *this = *this - other;
        return *this;
    }

    inline vector3 operator-()
    {
        return vector3(-x, -y, -z);
    }

    inline vector3 operator*(float s) const
    {
        return vector3(x * s, y * s, z * s);
    }

    inline friend vector3 operator*(float s, const vector3& rhs)
    {
        return rhs * s;
    }

    inline vector3& operator*=(float s)
    {
        *this = *this * s;
        return *this;
    }

    inline vector3 operator/(float s) const
    {
        s = 1.f / s;
        return vector3(x * s, y * s, z * s);
    }

    inline vector3& operator/=(float s)
    {
        *this = *this / s;
        return *this;
    }

    inline bool operator==(const vector3& other)
    {
        return x == other.x && y == other.y && z == other.z;
    }

    inline bool operator!=(const vector3& other)
    {
        return !(*this == other);
    }

    inline static float dot(const vector3& a, const vector3& b)
    {
        return a.dot(b);
    }

    inline static vector3 cross(const vector3& a, const vector3& b)
    {
        return a.cross(b);
    }

    inline static vector3 project(const vector3& a, const vector3& b)
    {
        return a.project(b);
    }

    inline static vector3 reflect(const vector3& inDir, const vector3& inNormal)
    {
        return -2.f * inDir.project(inNormal) + inDir;
    }

    inline static float angle(const vector3& a, const vector3& b)
    {
        return acos(dot(a.normalized(), b.normalized())) * math::rad2deg;
    }

    inline static vector3 lerp(const vector3& a, const vector3& b, float t)
    {
        return a + (b - a) * t;
    }

public:
    static const vector3 one;
    static const vector3 zero;
    static const vector3 up;
    static const vector3 down;
    static const vector3 left;
    static const vector3 right;
    static const vector3 forward;
    static const vector3 back;

public:
    float x;
    float y;
    float z;
};

NS_TINY3D_END

#endif//_VECTOR3_H_