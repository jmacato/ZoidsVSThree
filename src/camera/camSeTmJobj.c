#include "types.h"

extern s32 camSeTm(void *camera, s16 sound, f32 *point, s32 time);

s32 camSeTmJobj(void *camera, s16 sound, u8 *joint, s32 time)
{
    f32 point[3];
    s32 i;
    if (joint == 0)
        return 0;
    for (i = 0; i < 3; i++)
        point[i] = *(f32 *)(joint + 0x50 + (i << 4));
    return camSeTm(camera, sound, point, time);
}
