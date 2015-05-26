/************************************************
 * file  : matrix.cpp
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#include "matrix4.h"

NS_TINY3D_BEGIN

const matrix4 matrix4::identify = matrix4(1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0, 0, 0, 1);
const matrix4 matrix4::zero = matrix4(0, 0, 0, 0,
                                      0, 0, 0, 0,
                                      0, 0, 0, 0,
                                      0, 0, 0, 0);

NS_TINY3D_END