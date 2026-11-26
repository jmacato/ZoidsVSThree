#include "zoid3.h"

void zdEffectMountTm(ZoidState *zoid, s32 a, s32 b, s32 mode)
{
    s32 i;
    s32 *mount;
    if (zoid != 0 && zoid->joint != 0) {
        if (mode == 0) {
            mode = 1;
        }
        for (i = 0; i < 5; i++) {
            mount = zoid->effect_mounts[i];
            if (mount[0] == 0) {
                mount[0] = mode;
                mount[1] = a;
                mount[2] = b;
                return;
            }
        }
    }
}
