#include "zoid3.h"

void ZoidTargetSet(ZoidState *zoid, s32 index)
{
    ZoidState *target;
    s32 slot;
    s32 target_slot;

    if (zoid != (void *)0 && zoid->joint != (void *)0 && index >= 0 && index < 16) {
        target = &Zoid[index];
        if (target->joint != (void *)0 && target->stel_state != ZOID_STEL_ON &&
            zoid->target_visibility[index] != 0 &&
            !(zoid->search_range < zoid->distances[index])) {
            slot = zoid->slot;
            target_slot = target->slot;
            if (slot != target_slot) {
                zoid->target_slot = index;
                zoid->target_pending = 1;
            }
        }
    }
}
