#include "zoid3.h"

void zdAtkSub(ZoidState *zoid)
{
    register s32 i;
    register ZoidState *target;
    f32 best;
    register f32 d;
    f32 distance;

    if (zoid != (void *)0 && zoid->joint != (void *)0 && zoid->attack_target <= -1) {
        best = -1.0f;
        for (i = 0; i < 16; i++) {
            target = &Zoid[i];
            if (target->joint != (void *)0 && target->stel_state != 2 && zoid->attack_in_range[i] != 0 && !((d = zoid->distances[i]) <= 0.0f)) {
                if (best == -1.0f || distance > d) {
                    distance = zoid->distances[i];
                    best = i;
                }
            }
        }
        zoid->attack_target = best;
    }
}
