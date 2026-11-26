#include "zoid3.h"

typedef struct ZdColMask {
    u8 bits[4];
} ZdColMask;

extern f32 sLenPoint3dR(f32 *point);
extern f32 sColPt(f32 *start, f32 *end, ZdColMask *mask);

s32 zdCol(ZoidState *zoid, f32 *point, f32 radius)
{
    f32 end[3];
    f32 start[3];
    f32 length;
    s32 i;
    ZdColMask mask;
    f32 hit;

    if (zoid == 0)
        return 0;
    if (zoid->joint == 0)
        return 0;
    if (radius == 0.0f)
        return 0;
    length = sLenPoint3dR(point);
    if (length == 0.0f)
        return 0;
    for (i = 0; i < 3; i++) {
        end[i] = zoid->clip_point[i] + radius * point[i] / length;
        start[i] = zoid->clip_point[i] - 2.0f * point[i] / length;
    }
    mask = (ZdColMask){{0x13, 0, 0, 0}};
    hit = sColPt(start, end, &mask);
    if (10000.0f == hit)
        return 0;
    return 1;
}
