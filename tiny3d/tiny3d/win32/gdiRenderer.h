/************************************************
 * file  : gdiRenderer.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _GDIRENDERER_H_
#define _GDIRENDERER_H_

#include "../base/base.h"
#include "../graphic/renderer.h"
#include "gdiContext.h"

NS_TINY3D_BEGIN

class gdiRenderer : public renderer
{
public:
    gdiRenderer()
    {
        context = new gdiContext();
    }

    ~gdiRenderer()
    {
        delete context;
    }

    virtual bool initialize(int _width, int _height);
    virtual void uninitialize();
    virtual void clear();
    virtual void present();
    virtual void drawPixel(int x, int y);

public:
    gdiContext* context;
};

NS_TINY3D_END

#endif//_GDIRENDERER_H_
