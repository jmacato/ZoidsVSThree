#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

s32 zdAI_IsTarget(s32 index)
{
    ZoidState *zoid;

    aiCmdReport("aiCmd-isTarget \n");
    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return 0;
    }
    if (zoid->target_pending == 0) {
        return 0;
    }
    return 1;
}
