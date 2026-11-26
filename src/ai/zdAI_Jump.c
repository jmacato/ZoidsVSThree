#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

void zdAI_Jump(s32 index)
{
    ZoidState *zoid;

    aiCmdReport("aiCmd-jump \n");
    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0) {
            zoid->requested_action = ZOID_ACTION_JUMP_2;
        }
    }
}
