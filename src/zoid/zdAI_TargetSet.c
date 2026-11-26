#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void ZoidTargetSet(ZoidState *zoid, s32 index);

void zdAI_TargetSet(s32 index, s32 target)
{
    ZoidState *zoid;

    aiCmdReport("aiCmd-targetSet \n");
    if (index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0) {
            if (index < 0) {
                zoid->target_pending = 0;
            } else {
                ZoidTargetSet(zoid, target);
            }
        }
    }
}
