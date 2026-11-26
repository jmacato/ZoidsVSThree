#include "zoid3.h"

extern void jobjTransT(HSD_JObj *joint, f32 *translation);

void zdSetXYZ2(ZoidState *zoid)
{
    f32 position[3];
    s32 i;
    for (i = 0; i < 3; i++) {
        position[i] = zoid->position[i];
    }
    position[1] = position[1] + zoid->height_offset;
    jobjTransT(zoid->joint, position);
}
