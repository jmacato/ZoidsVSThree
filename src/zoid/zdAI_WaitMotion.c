#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void zdMotion(ZoidState *zoid, s32 motion);

void zdAI_WaitMotion(s32 index, s32 motion)
{
    ZoidState *zoid;
    ZoidAIState *ai;

    aiCmdReport("aiCmd-wait \n");
    if (index < 0) {
        return;
    }
    if (index >= 16) {
        return;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return;
    }
    ai = zoid->ai;
    if (ai == (void *)0) {
        return;
    }
    ai->mode = 0;
    zdMotion(zoid, motion);
}
