#include "types.h"

f32 sAngPoint3dRb(Vec3 *a, Vec3 *b)
{
    f32 dot = a->z * b->z + (a->x * b->x + a->y * b->y);

    return dot;
}
