/************************************************
 * file  : matrix.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "../base/base.h"
#include "math.h"
#include "vector3.h"
#include "vector4.h"
#include <math.h>
#include <memory.h>

NS_TINY3D_BEGIN

class matrix4
{
public:
    matrix4()
    {
        m00 = m01 = m02 = m03 = 
        m10 = m11 = m12 = m13 = 
        m20 = m21 = m22 = m23 = 
        m30 = m31 = m32 = m33 = 0;
    }

    matrix4(float _m00, float _m01, float _m02, float _m03,
        float _m10, float _m11, float _m12, float _m13,
        float _m20, float _m21, float _m22, float _m23,
        float _m30, float _m31, float _m32, float _m33)
    {
        m00 = _m00; m01 = _m01; m02 = _m02; m03 = _m03;
        m10 = _m10; m11 = _m11; m12 = _m12; m13 = _m13;
        m20 = _m20; m21 = _m21; m22 = _m22; m23 = _m23;
        m30 = _m30; m31 = _m31; m32 = _m32; m33 = _m33;
    }

    inline void transpose()
    {
        *this = matrix4(m00, m10, m20, m30,
            m01, m11, m21, m31,
            m02, m12, m22, m32,
            m03, m13, m23, m33);
    }

    inline matrix4 transposed() const
    {
        matrix4 m(*this);
        m.transpose();
        return m;
    }

    inline bool inverse()
    {
        float det = determinant();
        if (fabs(det) < math::eplison)
        {
            return false;
        }

        *this = adjoint() / det;
        return true;
    }

    inline matrix4 inversed() const
    {
        matrix4 m(*this);
        m.inverse();
        return m;
    }

    inline float determinant() const
    {
        return m00 * (m11 * (m22 * m33 - m23 * m32) + m12 * (m23 * m31 - m21 * m33) + m13 * (m21 * m32 - m22 * m31)) -
            m01 * (m10 * (m22 * m33 - m23 * m32) + m12 * (m23 * m30 - m20 * m33) + m13 * (m20 * m32 - m22 * m30)) + 
            m02 * (m10 * (m21 * m33 - m23 * m31) + m11 * (m23 * m30 - m20 * m33) + m13 * (m20 * m31 - m21 * m30)) -
            m03 * (m10 * (m21 * m32 - m22 * m31) + m11 * (m22 * m30 - m20 * m32) + m12 * (m20 * m31 - m21 * m30));
    }

    inline matrix4 adjoint() const
    {
        float c00 = +(m11 * (m22 * m33 - m23 * m32) + m12 * (m23 * m31 - m21 * m33) + m13 * (m21 * m32 - m22 * m31));
        float c01 = -(m10 * (m22 * m33 - m23 * m32) + m12 * (m23 * m30 - m20 * m33) + m13 * (m20 * m32 - m22 * m30));
        float c02 = +(m10 * (m21 * m33 - m23 * m31) + m11 * (m23 * m30 - m20 * m33) + m13 * (m20 * m31 - m21 * m30));
        float c03 = -(m10 * (m21 * m32 - m22 * m31) + m11 * (m22 * m30 - m20 * m32) + m12 * (m20 * m31 - m21 * m30));

        float c10 = -(m01 * (m22 * m33 - m23 * m32) + m02 * (m23 * m31 - m21 * m33) + m03 * (m21 * m32 - m22 * m31));
        float c11 = +(m00 * (m22 * m33 - m23 * m32) + m02 * (m23 * m30 - m20 * m33) + m03 * (m20 * m32 - m22 * m30));
        float c12 = -(m00 * (m21 * m33 - m23 * m31) + m01 * (m23 * m30 - m20 * m33) + m03 * (m20 * m31 - m21 * m30));
        float c13 = +(m00 * (m21 * m32 - m22 * m31) + m01 * (m22 * m30 - m20 * m32) + m02 * (m20 * m31 - m21 * m30));

        float c20 = +(m01 * (m12 * m33 - m13 * m32) + m02 * (m13 * m31 - m11 * m33) + m03 * (m11 * m32 - m12 * m31));
        float c21 = -(m00 * (m12 * m33 - m13 * m32) + m02 * (m13 * m30 - m10 * m33) + m03 * (m10 * m32 - m12 * m30));
        float c22 = +(m00 * (m11 * m33 - m13 * m31) + m01 * (m13 * m30 - m10 * m33) + m03 * (m10 * m31 - m11 * m30));
        float c23 = -(m00 * (m11 * m32 - m12 * m31) + m01 * (m12 * m30 - m10 * m32) + m02 * (m10 * m31 - m11 * m30));

        float c30 = -(m01 * (m12 * m23 - m13 * m22) + m02 * (m13 * m21 - m11 * m23) + m03 * (m11 * m22 - m12 * m21));
        float c31 = +(m00 * (m12 * m23 - m13 * m22) + m02 * (m13 * m20 - m10 * m23) + m03 * (m10 * m22 - m12 * m20));
        float c32 = -(m00 * (m11 * m23 - m13 * m21) + m01 * (m13 * m20 - m10 * m23) + m03 * (m10 * m21 - m11 * m20));
        float c33 = +(m00 * (m11 * m22 - m12 * m21) + m01 * (m12 * m20 - m10 * m22) + m02 * (m10 * m21 - m11 * m20));

        return matrix4(c00, c10, c20, c30,
            c01, c11, c21, c31, 
            c02, c12, c22, c32, 
            c03, c13, c23, c33);
    }

    inline matrix4 operator*(const matrix4& other) const
    {
        float c00 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30;
        float c01 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31;
        float c02 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32;
        float c03 = m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33;

        float c10 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30;
        float c11 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
        float c12 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
        float c13 = m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33;

        float c20 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30;
        float c21 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
        float c22 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
        float c23 = m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33;

        float c30 = m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30;
        float c31 = m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31;
        float c32 = m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32;
        float c33 = m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

        return matrix4(c00, c01, c02, c03,
            c10, c11, c12, c13, 
            c20, c21, c22, c23, 
            c30, c31, c32, c33);
    }

    inline friend vector3 operator*(const vector3& v, const matrix4& m)
    {
        float x = v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + m.m30;
        float y = v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + m.m31;
        float z = v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + m.m32;
        return vector3(x, y, z);
    }

    inline friend vector4 operator*(const vector4& v, const matrix4& m)
    {
        float x = v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30;
        float y = v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31;
        float z = v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32;
        float w = v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33;
        return vector4(x, y, z, w);
    }

    inline matrix4& operator*=(const matrix4& other)
    {
        m00 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30;
        m01 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31;
        m02 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32;
        m03 = m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33;

        m10 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30;
        m11 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
        m12 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
        m13 = m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33;

        m20 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30;
        m21 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
        m22 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
        m23 = m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33;

        m30 = m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30;
        m31 = m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31;
        m32 = m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32;
        m33 = m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

        return *this;
    }

    inline matrix4 operator*(float s) const
    {
        return matrix4(m00 * s, m01 * s, m02 * s, m03 * s,
            m10 * s, m11 * s, m12 * s, m13 * s,
            m20 * s, m21 * s, m22 * s, m23 * s,
            m30 * s, m31 * s, m32 * s, m33 * s);
    }

    inline friend matrix4 operator*(float s, const matrix4& m)
    {
        return m * s;
    }

    inline matrix4& operator*=(float s)
    {
        m00 *= s; m01 *= s; m02 *= s; m03 *= s;
        m10 *= s; m11 *= s; m12 *= s; m13 *= s;
        m20 *= s; m21 *= s; m22 *= s; m23 *= s;
        m30 *= s; m31 *= s; m32 *= s; m33 *= s;

        return *this;
    }

    inline matrix4 operator/(float s) const
    {
        return matrix4(m00 / s, m01 / s, m02 / s, m03 / s,
            m10 / s, m11 / s, m12 / s, m13 / s,
            m20 / s, m21 / s, m22 / s, m23 / s,
            m30 / s, m31 / s, m32 / s, m33 / s);
    }

    inline matrix4& operator/=(float s)
    {
        m00 /= s; m01 /= s; m02 /= s; m03 /= s;
        m10 /= s; m11 /= s; m12 /= s; m13 /= s;
        m20 /= s; m21 /= s; m22 /= s; m23 /= s;
        m30 /= s; m31 /= s; m32 /= s; m33 /= s;

        return *this;
    }

    inline bool operator==(const matrix4& other) const
    {
        return m00 == other.m00 && m01 == other.m01 && m02 == other.m02 && m03 == other.m03 && 
            m10 == other.m10 && m11 == other.m11 && m12 == other.m12 && m03 == other.m13 && 
            m20 == other.m20 && m21 == other.m21 && m22 == other.m22 && m03 == other.m23 && 
            m30 == other.m30 && m31 == other.m31 && m32 == other.m32 && m03 == other.m33;
    }

    inline bool operator!=(const matrix4& other) const
    {
        return !(*this == other);
    }

    inline static matrix4 translate(float x, float y, float z)
    {
        matrix4 m(identify);
        m.m30 = x;
        m.m31 = y;
        m.m32 = z;
        return m;
    }

    inline static matrix4 rotation(const vector3& axis, float angle)
    {
        vector3 n = axis.normalized();
        float r = angle * math::deg2rad;
        float c = cos(r), s = sin(r);
        return matrix4(
            n.x * n.x * (1.f - c) + c, n.x * n.y * (1.f - c) + n.z * s, n.x * n.z * (1.f - c) - n.y * s, 0,
            n.x * n.y * (1.f - c) - n.z * s, n.y * n.y * (1.f - c) + c, n.y * n.z * (1.f - c) + n.x * s, 0,
            n.x * n.z * (1.f - c) + n.y * s, n.y * n.z * (1.f - c) - n.x * s, n.z * n.z * (1.f - c) + c, 0,
            0, 0, 0, 1.f);
    }

    inline static matrix4 rotation(const vector3& euler)
    {
        matrix4 mx(identify), my(identify), mz(identify);
        vector3 radian = euler * math::deg2rad;

        float c = cos(radian.x);
        float s = sin(radian.x);
        mx.m11 = c; mx.m12 = s;
        mx.m21 =-s; mx.m22 = c;

        c = cos(radian.y);
        s = sin(radian.y);
        my.m00 = c; my.m02 =-s;
        my.m20 = s; my.m22 = c;

        c = cos(radian.z);
        s = sin(radian.z);
        mz.m00 = c; mz.m01 = s;
        mz.m10 =-s; mz.m11 = c;

        return mx * my * mz;
    }

    inline static matrix4 scale(float x, float y, float z)
    {
        matrix4 m(identify);
        m.m00 = x;
        m.m11 = y;
        m.m22 = z;
        return m;
    }

public:
    static const matrix4 identify;
    static const matrix4 zero;

public:
    float m00, m01, m02, m03, 
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33;
};

NS_TINY3D_END

#endif//_MATRIX4_H_