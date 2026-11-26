#include "types.h"

extern u8 mgI[];
extern void sLinear1D(f32 target, f32 *value, f32 speed);

void limitHigh(f32 *p)
{
    f32 lo = (f32)*(s32 *)(mgI + 0x3248);
    f32 hi = (f32)*(s32 *)(mgI + 0x324C);
    f32 speed;
    f32 v;
    if (lo < hi)
        return;
    v = p[1];
    speed = 1.0F;
    if (lo < v)
        v = lo;
    if (hi > v)
        v = hi;
    if (lo == v)
        speed = 10.0F;
    sLinear1D(v, &p[1], speed);
}
