#include "zoid3.h"

extern void zdEffectMount(ZoidState *zoid, s32 a, s32 b);

void zdEffectMountInt(ZoidState *zoid)
{
    s32 i;
    s32 *entry;

    if (zoid != 0 && zoid->joint != 0) {
        for (i = 0; i < 5; i++) {
            entry = &zoid->effect_mounts[i][0];
            if (entry[0] != 0) {
                entry[0] = entry[0] - 1;
                if (entry[0] <= 0) {
                    entry[0] = 0;
                    zdEffectMount(zoid, entry[1], entry[2]);
                    return;
                }
            }
        }
    }
}
