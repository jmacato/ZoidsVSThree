#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

void zdAI_SetLenIn(s32 index, f32 distance)
{
    aiCmdReport("aiCmd-setLenIn \n");
    zdAI_SetLen1(index, AI_RADIUS_IN, distance);
}
