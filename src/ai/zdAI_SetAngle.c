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

void zdAI_SetAngle(s32 index, s32 angle_mode, s32 degrees, s32 speed)
{
    ZoidState *zoid;
    AiAngleState *ai;

    aiCmdReport("aiCmd-setAngle \n");
    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0) {
            ai = (AiAngleState *)zoid->ai;
            if (ai != 0) {
                goFrom(zoid);
                ai->mode = AI_MODE_TARGET;
                ai->flags = (ai->flags & ~AI_ANGLE_MASK) | (angle_mode << AI_ANGLE_SHIFT);
                ai->target_angle = 2.0 * (3.1415926 * (f32)degrees) / 360.0;
                ai->turn_speed = speed;
            }
        }
    }
}
