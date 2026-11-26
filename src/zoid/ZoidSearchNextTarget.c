#include "zoid3.h"

extern s32 searchZoid1(ZoidState *zoid, s32 index);
extern void zdWeaponSightClearAll(ZoidState *zoid);

void ZoidSearchNextTarget(ZoidState *zoid)
{
    s32 index;
    s32 i;

    if (zoid == (void *)0) {
        return;
    }
    if (zoid->joint == (void *)0) {
        return;
    }
    if (zoid->death_started != 0) {
        return;
    }
    index = zoid->target_slot;
    for (i = 0; i < 16; i++) {
        index++;
        if (index >= 16) {
            index = 0;
        }
        if (index < 0) {
            index = 0;
        }
        if (searchZoid1(zoid, index) != 0) {
            zoid->target_slot = index;
            zoid->target_pending = 1;
            zdWeaponSightClearAll(zoid);
            return;
        }
    }
    zoid->target_pending = 0;
}
