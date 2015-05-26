/************************************************
 * file  : mesh.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _MESH_H_
#define _MESH_H_

#include "../base/base.h"
#include "../math/vector3.h"

NS_TINY3D_BEGIN

class mesh
{
public:
    vector3* vertices;
    int count;
};

NS_TINY3D_END

#endif//_MESH_H_