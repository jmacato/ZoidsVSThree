#include "types.h"

extern f32 atan2f(f32 y, f32 x);

f32 calcAng1(Vec3 *v)
{
    f32 x;
    f32 z;

    x = v->x;
    z = v->z;
    if (0.0f == x && 0.0f == z) {
        return 100.0f;
    }
    return atan2f(x, z);
}
