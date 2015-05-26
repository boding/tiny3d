/************************************************
 * file  : tiny3d.h
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#ifndef _TINY3D_H_
#define _TINY3D_H_

#include "base/base.h"

#include "math/math.h"
#include "math/vector2.h"
#include "math/vector3.h"
#include "math/vector4.h"
#include "math/matrix4.h"
#include "math/quaternion.h"

#include "graphic/renderer.h"
#include "graphic/color.h"
#include "graphic/camera.h"

#include "geometry/line.h"
#include "geometry/triangle.h"
#include "geometry/obj.h"
#include "geometry/cube.h"

#if defined(_WIN32)
#include "win32/gdiRenderer.h"
#endif

#endif//_TINY3D_H_