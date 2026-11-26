#include "ground_collision.h"

extern void sColPosGetXZ(s32 *column, s32 *row, f32 x, f32 z);

s32 sColPos(Vec3 *point)
{
    s32 column;
    s32 row;
    register f32 x = point->x;
    register f32 z = point->z;

    sColPosGetXZ(&column, &row, x, z);
    return column + row * grdcDivX;
}
