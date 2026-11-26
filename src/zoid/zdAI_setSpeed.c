#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

typedef struct AiSpeedState {
    u8 reserved_00[0xB0];
    f32 set_speed;
} AiSpeedState;

void zdAI_setSpeed(s32 index, s32 speed)
{
    ZoidState *zoid;
    AiSpeedState *ai;
    void *anim;

    aiCmdReport("aiCmd-setSpeed \n");
    if (index < 0) {
        return;
    }
    if (index >= 16) {
        return;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return;
    }
    ai = (AiSpeedState *)zoid->ai;
    if (ai == 0) {
        return;
    }
    anim = zoid->anim_data;
    if (anim == 0) {
        return;
    }
    ai->set_speed = (zoid->field_1F04 / 100.0) * speed / 100.0;
}
