/************************************************
 * file  : gdiContext.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _GDICONTEXT_H_
#define _GDICONTEXT_H_

#include "../base/base.h"
#include <windows.h>

NS_TINY3D_BEGIN

class gdiContext
{
public:
    bool initialize(int _width, int _height);
    void uninitialize();

public:
    HWND hwnd;
    HDC wndDc;
    HDC memDc;
    HBITMAP bitmap;
    int width;
    int height;
};

NS_TINY3D_END

#endif//_GDICONTEXT_H_
