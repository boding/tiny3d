/************************************************
 * file  : renderer.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#include "renderer.h"
#include <algorithm>

NS_TINY3D_BEGIN

bool renderer::initialize(int _width, int _height)
{
    return false;
}

void renderer::uninitialize()
{
}

void renderer::clear()
{
}

void renderer::present()
{
}

void renderer::drawPixel(int x, int y)
{
}

void renderer::drawLine(const line& l)
{
    float dx = l.p0.x - l.p1.x;
    float dy = l.p0.y - l.p1.y;

    if (fabs(dx) < math::eplison)
    {
        int y0 = (int)(l.p0.y < l.p1.y ? l.p0.y : l.p1.y);
        int y1 = (int)(l.p0.y < l.p1.y ? l.p1.y : l.p0.y);
        int x = (int)l.p0.x;
        for (int y=y0; y<y1; ++y)
        {
            drawPixel(x, y);
        }
    }
    else if (fabs(dy) < math::eplison)
    {
        int x0 = (int)(l.p0.x < l.p1.x ? l.p0.x : l.p1.x);
        int x1 = (int)(l.p0.x < l.p1.x ? l.p1.x : l.p0.x);
        int y = (int)l.p0.y;
        for (int x=x0; x<x1; ++x)
        {
            drawPixel(x, y);
        }
    }
    else
    {
        if (fabs(dx) > fabs(dy))
        {
            int x0 = (int)(l.p0.x < l.p1.x ? l.p0.x : l.p1.x);
            int x1 = (int)(l.p0.x < l.p1.x ? l.p1.x : l.p0.x);
            float y = l.p0.x < l.p1.x ? l.p0.y : l.p1.y;
            float k = dy / dx;

            for (int x=x0; x<x1; ++x)
            {
                drawPixel(x, (int)y);
                y += k;
            }
        }
        else
        {
            int y0 = (int)(l.p0.y < l.p1.y ? l.p0.y : l.p1.y);
            int y1 = (int)(l.p0.y < l.p1.y ? l.p1.y : l.p0.y);
            float x = l.p0.y < l.p1.y ? l.p0.x : l.p1.x;
            float k = dx / dy;

            for (int y=y0; y<y1; ++y)
            {
                drawPixel((int)x, y);
                x += k;
            }
        }
    }
}

void renderer::drawTriangle(const triangle& t)
{
    drawLine(line(t.p0, t.p1));
    drawLine(line(t.p1, t.p2));
    drawLine(line(t.p2, t.p0));
}

void fillTriangleFlatTop(renderer* r, vector3 t, vector3 m, vector3 b)
{
    if (t.x > m.x) std::swap(t, m);

    float k1 = (t.x - b.x) / (t.y - b.y);
    float k2 = (m.x - b.x) / (m.y - b.y);
    float x1 = b.x, x2 = b.x;

    int yt = math::round(t.y), yb = math::round(b.y);
    for (int y=yb; y<=yt; ++y)
    {
        int xl = math::round(x1), xr = math::round(x2);
        for (int x=xl; x<=xr; ++x)
        {
            r->drawPixel(x, y);
        }
        x1 += k1; x2 += k2;
    }
}

void fillTirangleFlatBottom(renderer* r, vector3 t, vector3 m, vector3 b)
{
    if (b.x > m.x) std::swap(b, m);

    float k1 = (t.x - b.x) / (t.y - b.y);
    float k2 = (t.x - m.x) / (t.y - m.y);
    float x1 = b.x, x2 = m.x;

    int yt = math::round(t.y), yb = math::round(b.y);
    for (int y=yb; y<=yt; ++y)
    {
        int xl = math::round(x1), xr = math::round(x2);
        for (int x=xl; x<=xr; ++x)
        {
            r->drawPixel(x, y);
        }
        x1 += k1; x2 += k2;
    }
}

void renderer::fillTriangle(const triangle& t)
{
    vector3 pt = t.p0, pm = t.p1, pb = t.p2;
    if (pt.y < pm.y) std::swap(pt, pm);
    if (pt.y < pb.y) std::swap(pt, pb);
    if (pm.y < pb.y) std::swap(pm, pb);

    if (pt.y - pm.y < math::eplison)
    {
        fillTriangleFlatTop(this, pt, pm, pb);
    }
    else if (pm.y - pb.y < math::eplison)
    {
        fillTirangleFlatBottom(this, pt, pm, pb);
    }
    else
    {
        vector3 pn = pt + (pb - pt) * (pm.y - pt.y) / (pb.y - pt.y);
        fillTirangleFlatBottom(this, pt, pm, pn);

        pn = pt + (pb - pt) * (pm.y - 1.f - pt.y) / (pb.y - pt.y);
        fillTriangleFlatTop(this, pm, pn, pb);
    }
}

void renderer::drawMesh(const mesh& m)
{

}

void renderer::drawObj(const obj& o)
{
    vector3* vertices = o.vertices;
    obj::face* faces = o.faces;

    for (int i=0; i<o.numFaces; ++i)
    {
        int* v = o.faces[i].v;
        drawTriangle(triangle(vertices[v[0]], vertices[v[1]], vertices[v[2]]));
        drawTriangle(triangle(vertices[v[1]], vertices[v[2]], vertices[v[3]]));
    }
}

float angle = 0;

void renderer::drawCube(const cube& cb, const camera& cam)
{
    matrix4 mat = matrix4::rotation(vector3(0, ++angle, 0));

    vector3 v[8];
    for (int i=0; i<8; ++i)
    {
        v[i] = cam.world2view(cb.v[i] * mat);
    }

    drawLine(line(v[0], v[1]));
    drawLine(line(v[1], v[2]));
    drawLine(line(v[2], v[3]));
    drawLine(line(v[3], v[0]));

    drawLine(line(v[4], v[5]));
    drawLine(line(v[5], v[6]));
    drawLine(line(v[6], v[7]));
    drawLine(line(v[7], v[4]));

    drawLine(line(v[0], v[4]));
    drawLine(line(v[1], v[5]));
    drawLine(line(v[2], v[6]));
    drawLine(line(v[3], v[7]));
}

NS_TINY3D_END