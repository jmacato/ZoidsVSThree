#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

void zdAI_SetLen(s32 index, f32 distance)
{
    aiCmdReport("aiCmd-setLen \n");
    zdAI_SetLen1(index, AI_RADIUS_EXACT, distance);
}
