#include "zoid3.h"

extern s32 grdObjGetMax(void);
extern s32 searchZoid1(ZoidState *zoid, s32 index);
extern s32 searchObj1(ZoidState *zoid, s32 index);
extern void zdWeaponSightClearAll(ZoidState *zoid);

void ZoidSearchNextTargetObj(ZoidState *zoid)
{
    register s32 pos;
    s32 max;
    s32 i;

    if (zoid != (void *)0 && zoid->joint != (void *)0 && zoid->death_started == 0) {
        max = grdObjGetMax();
        pos = 0;
        if (zoid->target_pending != 0) {
            pos = zoid->target_slot;
        }
        if (zoid->lock_active != 0) {
            pos = zoid->lock_obj - max;
        }
        for (i = 0; i < max + 0x10; i++) {
            pos++;
            if (pos >= 0x10) {
                pos = -max;
            }
            if (pos < -max) {
                pos = -max;
            }
            if (pos >= 0) {
                if (searchZoid1(zoid, pos) == 0) {
                    continue;
                }
                zoid->target_slot = pos;
                zoid->target_pending = 1;
                zoid->lock_active = 0;
            } else {
                if (searchObj1(zoid, pos + max) == 0) {
                    continue;
                }
                zoid->lock_obj = pos + max;
                zoid->target_pending = 0;
                zoid->lock_active = 1;
            }
            zdWeaponSightClearAll(zoid);
            return;
        }
        zoid->target_pending = 0;
        zoid->lock_active = 0;
    }
}
