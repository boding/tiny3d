/************************************************
 * file  : vector3.cpp
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#include "vector3.h"

NS_TINY3D_BEGIN

const vector3 vector3::one = vector3(1.f, 1.f, 1.f);
const vector3 vector3::zero = vector3(0, 0, 0);
const vector3 vector3::up = vector3(0, 1.f, 0);
const vector3 vector3::down = vector3(0, -1.f, 0);
const vector3 vector3::left = vector3(-1.f, 0, 0);
const vector3 vector3::right = vector3(1.f, 0, 0);
const vector3 vector3::forward = vector3(0, 0, 1.f);
const vector3 vector3::back = vector3(0, 0, -1.f);

NS_TINY3D_END