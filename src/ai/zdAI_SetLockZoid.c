#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

void zdAI_SetLockZoid(s32 index)
{
    ZoidState *zoid;
    s32 slot;

    aiCmdReport("aiCmd-setLockZoid \n");
    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0) {
            slot = zoid->target_slot;
            zdAI_SetZoid0(index, slot);
        }
    }
}
