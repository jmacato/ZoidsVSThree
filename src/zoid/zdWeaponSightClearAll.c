#include "zoid3.h"

extern void zdWeaponSightClear(ZoidState *zoid, s32 mount);

void zdWeaponSightClearAll(ZoidState *zoid)
{
    s32 i;
    for (i = 0; i < 20; i++) {
        zdWeaponSightClear(zoid, i);
    }
}
