#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

void zdAI_SetAngleSpd(s32 index, s32 speed)
{
    aiCmdReport("aiCmd-setAngleSpd \n");
    zdAI_SetAngle(index, AI_ANGLE_CIRCLE, 0, speed);
}
