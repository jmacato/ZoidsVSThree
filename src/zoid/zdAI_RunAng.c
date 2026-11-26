#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void goFrom(ZoidState *zoid);

typedef struct AiState3 {
    u8 pad_00[0x40];
    s32 mode;
    u32 flags;
    u8 pad_48[0x1C];
    f32 target_distance;
    u8 pad_68[0x8];
    s32 turn_speed;
} AiState3;

void zdAI_RunAng(s32 index, s32 degrees)
{
    ZoidState *zoid;
    AiState3 *ai;

    aiCmdReport("aiCmd-runAng \n");
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
    ai = (AiState3 *)zoid->ai;
    if (ai != 0) {
        goFrom(zoid);
        ai->mode = 4;
        ai->flags = 0;
        ai->turn_speed = degrees;
        ai->target_distance = 0.0f;
    }
}
