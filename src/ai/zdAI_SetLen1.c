#include "zoid3.h"

extern void aiCmdReport(const char *msg);

void zdAI_SetLen1(s32 index, f32 distance, u32 radius_mode)
{
    ZoidState *zoid;
    ZoidAIState *ai;

    aiCmdReport("aiCmd-setLen1 \n");
    if (index < 0) {
        return;
    }
    if (index >= 16) {
        return;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return;
    }
    ai = zoid->ai;
    if (ai != 0) {
        ai->target_distance = distance;
        ai->flags = (ai->flags & ~AI_RADIUS_MASK) | radius_mode;
    }
}
