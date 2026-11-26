#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

s32 zdAI_IsAtack(s32 index)
{
    ZoidState *zoid;
    ZoidState *other;
    s32 i;

    aiCmdReport("aiCmd-isAtack \n");
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
    for (i = 0; i < 16; i++) {
        other = &Zoid[i];
        if (other->joint != (void *)0 && other->field_1E50 == 0 && zoid->attack_in_range[i] == 1) {
            return 1;
        }
    }
    return 0;
}
