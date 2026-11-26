#include "types.h"

extern u8 *mgP;

void getWarn(f32 *src, f32 *dst)
{
    s32 i;
    for (i = 0; i < 3; i++)
        dst[0] = 0.0F;
    if (mgP == 0)
        return;
    if (*(s32 *)(mgP + 0x322C) == 0)
        return;
    for (i = 0; i < 3; i++)
        dst[i] = src[i];
    if (*(s32 *)(mgP + 0x322C) & 1)
        dst[2] = (f32)*(s32 *)(mgP + 0x3234);
    if ((*(s32 *)(mgP + 0x322C) + 1) & 1)
        dst[0] = (f32)*(s32 *)(mgP + 0x3230);
}
