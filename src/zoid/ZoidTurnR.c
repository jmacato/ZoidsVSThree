#include "zoid3.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern void angLimit(f32 *angle);
extern void zdChgNormal(ZoidState *zoid);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void ZoidTurnR(ZoidState *zoid, s32 mode)
{
    u8 *control;
    f32 turn;
    f32 speed;
    f32 diff;

    control = zoid->field_2090;
    if (control == 0) {
        turn = 90.0f;
    } else {
        turn = (f32) * (s32 *)(control + 0x154);
    }
    if (turn <= 0.0f) {
        zoid->action = 0;
        return;
    }
    speed = absf(zoid->field_1C54);
    switch (zoid->action_phase) {
    case 0:
        ZoidSetAnim(zoid, 12);
        zoid->action_phase = 1;
        break;
    case 1:
        if (mode == 0 && speed < 0.04) {
            zoid->animation_stopped = 1;
        }
        if (mode == 0 && (zoid->target_pending != 0 || zoid->lock_active != 0) && zoid->ai_active == 0) {
            diff = zoid->step_heading - zoid->heading;
            angLimit(&diff);
            if (diff >= 0.0f) {
                zoid->animation_stopped = 1;
            }
        }
        if (zoid->ai_active == 0 && zoid->target_pending == 0 && zoid->lock_active == 0 && zoid->field_1C74 < 0.0f) {
            zoid->animation_stopped = 1;
        }
        if (mode == 2 && zoid->target_pending != 0 && zoid->target_slot < 16 &&
            absf(zoid->target_angles[zoid->target_slot]) < DEG(5)) {
            zoid->animation_stopped = 1;
        }
        if (mode == 3) {
            diff = zoid->field_1C58 - zoid->heading;
            angLimit(&diff);
            if (diff >= 0.0f) {
                zdChgNormal(zoid);
                if (absf(diff) < DEG(3)) {
                    zoid->heading = zoid->field_1C58;
                    break;
                } else {
                    zoid->requested_action = 7;
                    break;
                }
            }
        }
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->action = 0;
            *(f32 *)(*(u8 **)((u8 *)zoid->pose + 4) + 0x10) = 0.0f;
            ZoidSetAnim(zoid, 1);
            HSD_JObjAnimAll(zoid->joint);
        } else {
            zoid->heading -= DEG(turn / 20.0f);
        }
        if (mode == 3) {
            diff = zoid->field_1C58 - zoid->heading;
            angLimit(&diff);
            if (diff >= 0.0f) {
                zoid->heading = zoid->field_1C58;
                zdChgNormal(zoid);
            }
        }
        break;
    }
}
