#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

void zdAI_SetAngleON(s32 index, s32 degrees)
{
    aiCmdReport("aiCmd-setAngleOn \n");
    zdAI_SetAngle(index, AI_ANGLE_KEEP, degrees, 0);
}
