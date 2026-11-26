#include "types.h"

extern s32 camSeTm(void *camera, s16 sound, f32 *point, s32 time);

s32 camSe(void *camera, s16 sound, f32 *point)
{
    return camSeTm(camera, sound, point, -1);
}
