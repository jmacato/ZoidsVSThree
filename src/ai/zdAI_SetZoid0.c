#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void goFrom(ZoidState *zoid);

void zdAI_SetZoid0(s32 index, s32 target)
{
    ZoidAIState *ai;
    ZoidState *zoid;
    ZoidState *other;

    aiCmdReport("aiCmd-setZoid0 \n");
    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0) {
            ai = zoid->ai;
            if (ai != 0) {
                if (target == -1) {
                    ai->target_index = target;
                    ai->mode = AI_MODE_TARGET;
                    ai->flags = 0;
                } else {
                    other = &Zoid[target];
                    if (other->joint != (void *)0) {
                        ai = zoid->ai;
                        if (ai != (void *)0) {
                            goFrom(zoid);
                            ai->target_index = target;
                            ai->mode = AI_MODE_TARGET;
                            ai->flags = 0;
                        }
                    }
                }
            }
        }
    }
}
