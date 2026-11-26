#include "zoid3.h"
#include "zoid_ai.h"

typedef struct AiState3 {
    s32 nearest_enemies[16];
    s32 mode;
    u32 flags;
    s32 target_index;
    Vec3 destination;
    Vec3 field_58;
    f32 target_distance;
    s32 field_68;
    f32 target_angle;
    s32 turn_speed;
} AiState3;

extern void aiCmdReport(const char *msg);
extern void goFrom(ZoidState *zoid);
extern f32 zdColPosY(Vec3 *pos, s32 mode);

void zdAI_rotPoint(s32 index, f32 x, f32 z, f32 distance, f32 angle)
{
    ZoidState *zoid;
    AiState3 *ai;

    aiCmdReport("aiCmd-rotPoint \n");
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
    if (ai == (void *)0) {
        return;
    }
    goFrom(zoid);
    ai->mode = 1;
    ai->flags = 0x21;
    ai->turn_speed = (s32)(angle / (2.0 * 3.1415926) * 360.0);
    ai->target_distance = distance;
    ai->destination.x = x;
    ai->destination.z = z;
    ai->destination.y = 100.0f;
    ai->destination.y = 100.0f + zdColPosY(&ai->destination, 0);
    ai->destination.y = zdColPosY(&ai->destination, 0);
}
