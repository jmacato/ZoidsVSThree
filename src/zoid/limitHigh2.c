#include "types.h"

extern u8 mgI[];
extern void sLinear1D(f32 *range, f32 value, f32 rate);

void limitHigh2(f32 *range)
{
    f32 limit = range[1];
    f32 value = (f32)*(s32 *)(mgI + 0x3248);
    if (!(value >= limit))
        sLinear1D(&range[1], value, 10.0F);
}
