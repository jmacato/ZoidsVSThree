#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

s32 zdAI_lenStep(s32 index)
{
    ZoidState *zoid;
    void *anim;
    s32 value;

    aiCmdReport("aiCmd-lenStep \n");
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
    anim = zoid->anim_data;
    if (anim == 0) {
        return 0;
    }
    value = *(s32 *)((u8 *)anim + 0xd0);
    return value / 2;
}
