#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

s32 zdAI_coHead(s32 index)
{
    ZoidState *zoid;

    aiCmdReport("aiCmd-coHead \n");
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
    return *(void **)(zoid->head_coobj + 0x18) != 0 || *(void **)(zoid->neck_coobj + 0x18) != 0;
}
