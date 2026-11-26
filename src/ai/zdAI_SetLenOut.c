#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

void zdAI_SetLenOut(s32 index, f32 distance)
{
    aiCmdReport("aiCmd-setLenOut \n");
    zdAI_SetLen1(index, AI_RADIUS_OUT, distance);
}
