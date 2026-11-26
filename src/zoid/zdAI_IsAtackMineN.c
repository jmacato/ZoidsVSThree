#include "zoid3.h"

extern void aiCmdReport(const char *msg);

s32 zdAI_IsAtackMineN(s32 index)
{
    ZoidState *zoid;
    ZoidState *other;
    s32 action;
    s32 i;

    aiCmdReport("aiCmd-isAtackMineN \n");
    if (index < 0) {
        return -1;
    }
    if (index >= 16) {
        return -1;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (i == index) {
            continue;
        }
        other = &Zoid[i];
        if (other->joint == (void *)0) {
            continue;
        }
        if (other->attack_in_range[index] == 0) {
            continue;
        }
        action = other->action;
        if (action >= 13 && action <= 22) {
            return i;
        }
    }
    return -1;
}
