/************************************************
 * file  : quaternion.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "../base/base.h"
#include "vector3.h"
#include "math.h"

NS_TINY3D_BEGIN

class quaternion
{
public:
    quaternion()
        : x(0), y(0), z(0), w(0)
    {}

    quaternion(float _x, float _y, float _z, float _w)
        : x(_x), y(_y), z(_z), w(_w)
    {}

    inline void fromEulerAngles(const vector3& angles)
    {
        float theta = angles.x * math::deg2rad * 0.5f;
        quaternion qx(sin(theta), 0, 0, cos(theta));

        theta = angles.y * math::deg2rad * 0.5f;
        quaternion qy(0, sin(theta), 0, cos(theta));

        theta = angles.z * math::deg2rad * 0.5f;
        quaternion qz(0, 0, sin(theta), cos(theta));

        *this = qx.cross(qy).cross(qz);
    }

    inline vector3 toEulerAngles() const
    {
        quaternion q(*this);
        q.normalize();

        float _x = atan2(q.x * q.w + q.y * q.z, 0.5f - q.x * q.x - q.y * q.y);
        float _y = asin(2.f * (q.y * q.w - q.x * q.z));
        float _z = atan2(q.z * q.w + q.x * q.y, 0.5f - q.y * q.y - q.z * q.z);

        return vector3(_x, _y, _z) * math::rad2deg;
    }

    inline void fromAxisAngle(const vector3& axis, float angle)
    {
        float radian = angle * math::deg2rad * 0.5f;
        float c = cos(radian), s = sin(radian);
        x = s * axis.x;
        y = s * axis.y;
        z = s * axis.z;
        w = c;
    }

    inline void toAxisAngle(vector3& axis, float& angle) const
    {
        quaternion q(*this);
        q.normalize();

        float theta = acos(q.w);
        angle = theta * math::rad2deg * 2.f;

        float s = sin(theta);
        if (s > math::eplison)
        {
            axis = vector3(q.x, q.y, q.z) / s;
        }
    }

    inline void normalize()
    {
        float magnitude = this->magnitude();
        if (magnitude > math::eplison)
        {
            *this /= magnitude;
        }
    }

    inline quaternion normalized() const
    {
        quaternion q(*this);
        q.normalize();
        return q;
    }

    inline float dot(const quaternion& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    inline quaternion cross(const quaternion& other) const
    {
        float _x = x * other.w + y * other.z - z * other.y + w * other.x;
        float _y =-x * other.z + y * other.w + z * other.x + w * other.y;
        float _z = x * other.y - y * other.x + z * other.w + w * other.z;
        float _w =-x * other.x - y * other.y - z * other.z + w * other.w;
        return quaternion(_x, _y, _z, _w);
    }

    inline void conjugate()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    inline quaternion conjugated() const
    {
        quaternion q(*this);
        q.conjugate();
        return q;
    }

    inline bool inverse()
    {
        float n = sqrMagnitude();
        if (n < math::eplison)
        {
            return false;
        }

        *this = conjugated() / n;
        return true;
    }

    inline quaternion inversed() const
    {
        quaternion q(*this);
        q.inverse();
        return q;
    }

    inline bool exponent(float t)
    {
        if (fabs(w) > 1.f - math::eplison)
        {
            return false;
        }
        float theta = acos(w);
        float s = sin(theta * t) / sin(theta);
        x *= s;
        y *= s;
        z *= s;
        w = cos(theta * t);
        return true;
    }

    inline quaternion exponented(float t)
    {
        quaternion q(*this);
        q.exponent(t);
        return q;
    }

    inline float magnitude()
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    inline float sqrMagnitude()
    {
        return x * x + y * y + z * z + w * w;
    }

    inline quaternion operator-() const
    {
        return quaternion(-x, -y, -z, -w);
    }

    inline quaternion operator*(float s) const
    {
        return quaternion(x * s, y * s, z * s, w * s);
    }

    inline quaternion& operator*=(float s)
    {
        *this = *this * s;
        return *this;
    }

    inline quaternion operator/(float s) const
    {
        s = 1.f / s;
        return quaternion(x * s, y * s, z * s, w * s);
    }

    inline quaternion& operator/=(float s)
    {
        *this = *this / s;
        return *this;
    }

    inline friend vector3 operator*(const vector3& v, const quaternion& q)
    {
        quaternion qv(v.x, v.y, v.z, 0);
        quaternion qr = q.cross(qv).cross(q.inversed());
        return vector3(qr.x, qr.y, qr.z);
    }

    inline bool operator==(const quaternion& other) const
    {
        return dot(other) >= 1.f - math::eplison;
    }

    inline bool operator!=(const quaternion& other) const
    {
        return !(*this == other);
    }

    inline static quaternion lerp(const quaternion& a, const quaternion& b, float t)
    {
        t = math::clamp(t, 0.f, 1.f);
        quaternion q = (a.dot(b) < 0) ? (-a) : a;
        float _x = (1.f - t) * q.x + t * b.x;
        float _y = (1.f - t) * q.y + t * b.y;
        float _z = (1.f - t) * q.z + t * b.z;
        float _w = (1.f - t) * q.w + t * b.w;
        return quaternion(_x, _y, _z, _w).normalized();
    }

    inline static quaternion slerp(const quaternion& a, const quaternion& b, float t)
    {
        t = math::clamp(t, 0.f, 1.f);
        float c = a.dot(b);
        quaternion q = c < 0 ? -a : a;
        c = c < 0 ? -c : c;

        float k0, k1;
        if (c > 1.f - math::eplison)
        {
            k0 = 1.f - t;
            k1 = t;
        }
        else
        {
            float s = sqrt(1.f - c * c);
            float omega = atan2(s, c);
            k0 = sin((1.f - t) * omega) / s;
            k1 = sin(t * omega) / s;
        }

        float _x = k0 * q.x + k1 * b.x;
        float _y = k0 * q.y + k1 * b.y;
        float _z = k0 * q.z + k1 * b.z;
        float _w = k0 * q.w + k1 * b.w;

        return quaternion(_x, _y, _z, _w).normalized();
    }

    inline static float angle(const quaternion& a, const quaternion& b)
    {
        return acos(fabs(a.dot(b))) * math::rad2deg * 2.f;
    }

public:
    static const quaternion identify;

public:
    float x;
    float y;
    float z;
    float w;
};

NS_TINY3D_END

#endif//_QUATERNION_H_