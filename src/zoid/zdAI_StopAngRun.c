#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void goFrom(ZoidState *zoid);

typedef struct AiAngleState {
    u8 reserved_00[0x40];
    s32 mode;
    u32 flags;
    u8 reserved_48[0x24];
    f32 target_angle;
    s32 turn_speed;
} AiAngleState;

void zdAI_StopAngRun(s32 index, s32 degrees)
{
    ZoidState *zoid;
    AiAngleState *ai;

    aiCmdReport("aiCmd-stopAngRun \n");
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
    ai = (AiAngleState *)zoid->ai;
    if (ai == 0) {
        return;
    }
    if (ai->mode == 6) {
        return;
    }
    goFrom(zoid);
    ai->mode = 6;
    ai->flags = 0;
    ai->target_angle = zoid->heading + (2.0 * (3.1415926 * (f32)degrees)) / 360.0;
}
