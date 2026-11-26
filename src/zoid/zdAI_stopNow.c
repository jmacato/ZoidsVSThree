#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

void zdAI_stopNow(s32 index)
{
    ZoidState *zoid;
    ZoidAIState *ai;

    aiCmdReport("aiCmd-stopNow \n");
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
    if (ai != 0) {
        zoid->field_1C90[0] = 0.0f;
        zoid->field_1C90[2] = 0.0f;
        zoid->field_1C90[1] = 0.0f;
        zoid->field_1C54 = 0.0f;
        ai->mode = 999;
    }
}
