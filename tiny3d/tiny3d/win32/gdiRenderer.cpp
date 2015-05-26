/************************************************
 * file  : gdiRenderer.cpp
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#include "gdiRenderer.h"

NS_TINY3D_BEGIN

bool gdiRenderer::initialize(int _width, int _height)
{
    width = _width;
    height = _height;

    return context->initialize(_width, _height);
}

void gdiRenderer::uninitialize()
{
    context->uninitialize();
}

void gdiRenderer::clear()
{
    RECT rc = { 0, 0, width, height };
    FillRect(context->memDc, &rc, 0);
}

void gdiRenderer::present()
{
    BitBlt(context->wndDc, 0, 0, width, height, context->memDc, 0, 0, SRCCOPY);
}

void gdiRenderer::drawPixel(int x, int y)
{
    SetPixel(context->memDc, x, y, 0);
}

NS_TINY3D_END