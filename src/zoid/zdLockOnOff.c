#include "zoid3.h"

extern s32 grdObjAliveN(s32 index);

void zdLockOnOff(ZoidState *zoid)
{
    s32 index;
    ZoidState *target;

    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    if (zoid->death_started != 0) {
        return;
    }
    if (zoid->target_pending == 0) {
        zoid->target_slot = 0;
    } else {
        index = zoid->target_slot;
        if (index < 0 || index >= 16) {
            index = -1;
        }
        if (index != -1) {
            target = &Zoid[index];
            if (target->lock_frames > 60) {
                index = -1;
            }
        }
        if (index == -1) {
            zoid->target_slot = 0;
            zoid->target_pending = 0;
        }
    }
    if (zoid->lock_active == 0) {
        zoid->lock_obj = 0;
        return;
    }
    if (grdObjAliveN(zoid->lock_obj) != 0) {
        return;
    }
    zoid->lock_obj = 0;
    zoid->lock_active = 0;
}
