#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern s32 zdAI_IsAtackMineN(s32 index);

s32 zdAI_IsAtackMine(s32 index)
{
    aiCmdReport("aiCmd-isAtackMine \n");
    return zdAI_IsAtackMineN(index) != -1;
}
