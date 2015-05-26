#include <windows.h>
#include <stdio.h>
#include "tiny3d/tiny3d.h"

using namespace tiny3d;

int main()
{
    int width = 640, height = 480;

    renderer* r = new gdiRenderer();
    r->initialize(width, height);

    camera* cam = new camera(1.f, 100.f, 90.f, width, height);
    cam->position = vector3(-320, -240, -1024);
    cam->rotation = vector3(0, 0, 0);
    cam->apply();

    vector3 v0[3] = 
    {
        vector3(  0,  0, 0),
        vector3( 50, 50, 0),
        vector3(100,  0, 0),
    };

    vector3 v1[3] = 
    {
        vector3(100, 200, 400),
        vector3(150, 250, 400),
        vector3(200, 200, 400),
    };

    quaternion q(quaternion::identify);
    float angle = 0;

    cube cb(vector3(0, 0, 0), 100);

    while (true)
    {
        r->clear();

        cam->rotation.x += 0.1f;
        if (cam->rotation.x >= 15)
        {
            cam->rotation.x = -15;
        }
        cam->apply();

        r->drawCube(cb, *cam);

//         q.fromEulerAngles(vector3(0, angle++, 0));
//         //cam->position = cam->position * q;
//         cam->rotation.y = angle;
//         cam->apply();
// 
//         vector3 v2[3] = 
//         {
//             c->world2view(v0[0] * q + vector3(100, 100, 320)),
//             c->world2view(v0[1] * q + vector3(100, 100, 320)),
//             c->world2view(v0[2] * q + vector3(100, 100, 320)),
//         };
// 
//         //r->fillTriangle(triangle(v2[0], v2[1], v2[2]));
//         r->drawTriangle(triangle(v2[0], v2[1], v2[2]));
// 
//         vector3 v3[3] = 
//         {
//             c->world2view(v1[0]),
//             c->world2view(v1[1]),
//             c->world2view(v1[2]),
//         };
// 
//         r->fillTriangle(triangle(v3[0], v3[1], v3[2]));
//         r->drawTriangle(triangle(v3[0], v3[1], v3[2]));

        r->present();
        Sleep(10);
    }

    r->uninitialize();

    return 0;
}