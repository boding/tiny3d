/************************************************
 * file  : color.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _COLOR_H_
#define _COLOR_H_

#include "../base/base.h"

NS_TINY3D_BEGIN

class color
{
public:
    color()
        : r(0), g(0), b(0), a(0)
    {}

    color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
        : r(_r), g(_g), b(_b), a(_a)
    {}

    inline color operator+(const color& other) const
    {
        return color(r + other.r, g + other.g, b + other.b, a + other.a);
    }

    inline color& operator+=(const color& other)
    {
        r += other.r;
        g += other.g;
        b += other.b;
        a += other.a;

        return *this;
    }

    inline color operator-(const color& other) const
    {
        return color(r - other.r, g - other.g, b - other.b, a - other.a);
    }

    inline color& operator-=(const color& other)
    {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        a -= other.a;
        return *this;
    }

    inline color operator*(float s) const
    {
        return color((unsigned char)(r * s), (unsigned char)(g * s), (unsigned char)(b * s), (unsigned char)(a * s));
    }

    inline friend color operator*(float s, const color& c)
    {
        return color((unsigned char)(c.r * s), (unsigned char)(c.g * s), (unsigned char)(c.b * s), (unsigned char)(c.a * s));
    }

    inline color& operator*=(float s)
    {
        r = (unsigned char)(r * s);
        g = (unsigned char)(g * s);
        b = (unsigned char)(b * s);
        a = (unsigned char)(a * s);
        return *this;
    }

    inline color operator/(float s) const
    {
        s = 1.f / s;
        return color((unsigned char)(r * s), (unsigned char)(g * s), (unsigned char)(b * s), (unsigned char)(a * s));
    }

    inline color& operator/=(float s)
    {
        s = 1.f / s;
        r = (unsigned char)(r * s);
        g = (unsigned char)(g * s);
        b = (unsigned char)(b * s);
        a = (unsigned char)(a * s);
        return *this;
    }

public:
    static const color red;
    static const color green;
    static const color blue;
    static const color white;
    static const color black;
    static const color gray;
    static const color yellow;
    static const color cyan;
    static const color magenta;

public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

NS_TINY3D_END

#endif//_COLOR_H_