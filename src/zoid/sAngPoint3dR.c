#include "types.h"

extern f32 sLenPoint3dR(Vec3 *point);
extern f32 sAngPoint3dRb(Vec3 *a, Vec3 *b);

f32 sAngPoint3dR(Vec3 *a, Vec3 *b)
{
    f32 product;

    product = sLenPoint3dR(a) * sLenPoint3dR(b);
    if (0.0f == product) {
        return 0.0f;
    }
    return sAngPoint3dRb(a, b) / product;
}
