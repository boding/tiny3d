/************************************************
 * file  : obj.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _OBJ_H_
#define _OBJ_H_

#include "../base/base.h"
#include "../math/vector3.h"
#include <stdio.h>
#include <vector>

NS_TINY3D_BEGIN

class obj
{
public:
    static obj* load(const char* file)
    {
        FILE* fp = fopen(file, "rb");
        if (0 == fp)
        {
            return 0;
        }

        std::vector<vector3> v;
        std::vector<face> f;

        char buffer[1024];
        while (fgets(buffer, 1024, fp))
        {
            if ('v' == buffer[0] && ' ' == buffer[1])
            {
                float x, y, z;
                sscanf(buffer, "v %f %f %f", &x, &y, &z);
                v.push_back(vector3(x, y, z));
            }
            else if ('f' == buffer[0] && ' ' == buffer[1])
            {
                int v[4], dummy;
                sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &dummy, &dummy, &v[1], &dummy, &dummy, &v[2], &dummy, &dummy, &v[3], &dummy, &dummy);
                v[0] -= 1;
                v[1] -= 1;
                v[2] -= 1;
                v[3] -= 1;
                f.push_back(face(v));
            }
        }
        fclose(fp);

        obj* o = new obj();
        o->numVertices = v.size();
        o->vertices = new vector3[v.size()];
        for (int i=0; i<o->numVertices; ++i)
        {
            o->vertices[i] = v[i];
        }

        o->numFaces = f.size();
        o->faces = new face[f.size()];
        for (int i=0; i<o->numFaces; ++i)
        {
            o->faces[i] = f[i];
        }

        return o;
    }

public:
    struct face 
    {
        int v[4];

        face() {}
        face(int _v[4])
        {
            v[0] = _v[0];
            v[1] = _v[1];
            v[2] = _v[2];
            v[3] = _v[3];
        }
    };

public:
    vector3* vertices;
    int numVertices;

    face* faces;
    int numFaces;
};

NS_TINY3D_END

#endif