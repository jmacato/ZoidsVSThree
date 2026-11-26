#include "zoid3.h"

extern f32 zdColPosY(f32 *point, u16 *selector);

f32 zdPosY(ZoidState *zoid, u16 *selector)
{
    f32 pos[3];
    s32 unused = zoid->camera_joint;
    s32 i;
    for (i = 0; i < 3; i++) {
        pos[i] = zoid->position[i];
    }
    return zdColPosY(pos, selector);
}
