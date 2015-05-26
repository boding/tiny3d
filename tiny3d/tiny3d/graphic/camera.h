/************************************************
 * file  : camera.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../base/base.h"
#include "../math/vector3.h"
#include "../math/matrix4.h"

NS_TINY3D_BEGIN

class camera
{
public:
    camera(float _near, float _far, float _fov, int _width, int _height)
        : Near(_near)
        , Far(_far)
        , fov(_fov)
        , width(_width)
        , height(_height)
        , wc(matrix4::identify)
    {
        aspect = (float)width / (float)height;
    }

    void apply();

    vector3 world2view(const vector3& world) const;

public:
    vector3 position;
    vector3 rotation;
    float Near;
    float Far;
    float fov;
    int width;
    int height;
    float aspect;
    matrix4 wc;
};

NS_TINY3D_END

#endif//_CAMERA_H_