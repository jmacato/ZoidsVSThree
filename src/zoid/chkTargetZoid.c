#include "zoid3.h"
#include "zoid_ai.h"


void chkTargetZoid(ZoidState *zoid)
{
    ZoidState *target;
    ZoidAIState *ai;
    s32 target_index;
    s32 alive;

    alive = 1;
    if (zoid != 0) {
        if (zoid->joint != 0) {
            ai = zoid->ai;
            if (ai != 0) {
                target_index = ai->target_index;
                if (target_index >= 0 && target_index < 16) {
                    target = &Zoid[target_index];
                    if (target->joint == 0) {
                        alive = 0;
                    }
                    if (target->death_started != 0) {
                        alive = 0;
                    }
                    if (alive == 0) {
                        ai->target_index = -1;
                        zoid->target_slot = 0xff;
                        zoid->target_pending = 0;
                    }
                }
            }
        }
    }
}
