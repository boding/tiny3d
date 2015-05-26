/************************************************
 * file  : renderer.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "../base/base.h"
#include "../geometry/line.h"
#include "../geometry/triangle.h"
#include "../geometry/mesh.h"
#include "../geometry/obj.h"
#include "../geometry/cube.h"
#include "../graphic/camera.h"

NS_TINY3D_BEGIN

class renderer
{
public:
    virtual bool initialize(int _width, int _height);
    virtual void uninitialize();
    virtual void clear();
    virtual void present();
    virtual void drawPixel(int x, int y);
    virtual void drawLine(const line& l);
    virtual void drawTriangle(const triangle& t);
    virtual void fillTriangle(const triangle& t);
    virtual void drawMesh(const mesh& m);
    virtual void drawObj(const obj& o);
    virtual void drawCube(const cube& cb, const camera& cam);

public:
    int width;
    int height;
};

NS_TINY3D_END

#endif//_RENDERER_H_
