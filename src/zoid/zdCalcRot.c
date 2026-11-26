#include "zoid3.h"
#include "angle.h"

extern void angLimit(f32 *angle);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void zdCalcRot(ZoidState *zoid)
{
    s32 fast = 0;
    s32 back;
    s32 ok;
    s32 turn_right;
    s32 turn_left;
    s32 walk;
    u8 *data;
    f32 turn;
    f32 step;
    f32 heading;
    f32 turnAbs;
    f32 diff;
    f32 tmp = 0.1f;

    if (zoid != (void *)0 && zoid->joint != (void *)0 && (data = zoid->anim_data) != 0 && zoid->jump_phase == 0 && zoid->action == 0 &&
        zoid->field_1360 == 0) {
        walk = zoid->current_animation;
        if (walk == 2) {
            (void)0;
        }
        step = zoid->step_heading;
        back = 0;
        turn_right = 0;
        turn_left = 0;
        heading = zoid->heading;
        diff = step - heading;
        angLimit(&diff);
        if (zoid->field_0170 != 0 && zoid->ai_active != 0 && zoid->ai != 0 && *(s32 *)((u8 *)zoid->ai + 0x40) != 0) {
            zoid->stick_angle = diff;
        }
        angLimit(&zoid->stick_angle);
        if (diff < -DEG2RAD_D(150) || diff > DEG2RAD_D(150)) {
            back = 1;
        } else {
            if (diff < -DEG2RAD_D(60)) {
                turn_right = 1;
            }
            if (diff > DEG2RAD_D(60)) {
                turn_left = 1;
            }
        }
        if (zoid->ai != 0 && *(s32 *)((u8 *)zoid->ai + 0x40) != 0) {
            ok = 1;
        } else {
            ok = 1;
        }
        turn = zoid->field_1C54;
        turnAbs = absf(turn);
        if (turnAbs > 0.2) {
            fast = 1;
        }
        if (zoid->field_1CA0 != 0) {
            zoid->field_1CA0--;
        }
        if (zoid->current_animation == 5) {
            if (0.9 * ((s32)*(s32 *)(data + 0xbc) / 100.0) < zoid->field_1C90[1]) {
                if (zoid->field_1C90[1] > 0.1) {
                    zoid->field_1CA0 = 5;
                }
            }
        }
        if (zoid->field_1CA0 != 0 && back != 0 && fast != 0 && zoid->field_0170 == 0) {
            zoid->requested_action = 12;
            zoid->action_phase = 0;
            zoid->field_1CA0 = 0;
            return;
        }
        if (zoid->field_0170 != 0) {
            back = 0;
        }
        if (zoid->ai_active != 0 && zoid->ai != 0 && *(s32 *)((u8 *)zoid->ai + 0x40) != 0) {
            back = 0;
        }
        if (zoid->field_0170 != 0 && zoid->ai_active != 0 && zoid->ai != 0 && *(s32 *)((u8 *)zoid->ai + 0x40) != 0) {
            turn_right = 0;
            turn_left = 0;
            fast = 0;
        }
        if (zoid->current_animation < 4 && ok != 0 && 0.0f == zoid->field_1C90[0]) {
            if (turn_right != 0) {
                if (fast != 0) {
                    zoid->requested_action = 4;
                    zoid->steer = 0.0f;
                }
                return;
            }
            if (turn_left != 0) {
                if (fast != 0) {
                    zoid->requested_action = 5;
                    zoid->steer = 0.0f;
                }
                return;
            }
        }
        if (back != 0 && fast != 0) {
            turn = -turn;
            diff += 3.1415926;
            angLimit(&diff);
            angLimit(&zoid->step_heading);
        }
        if (ok == 0) {
            turn = 0.0f;
        }
        zoid->steer = diff;
        if (absf(diff) < DEG2RAD_D(2)) {
            zoid->steer = 0.0f;
        }
        if (zoid->field_0170 != 0 && zoid->ai_active != 0 && zoid->ai != 0 && *(s32 *)((u8 *)zoid->ai + 0x40) != 0) {
            zoid->steer = diff;
        }
        if (diff < 0.0f) {
            if (diff < -DEG2RAD_D(2)) {
                zoid->steer = diff;
            } else {
                zoid->steer = 0.0f;
            }
        } else if (diff > DEG2RAD_D(2)) {
            zoid->steer = diff;
        } else {
            zoid->steer = 0.0f;
        }
        if (turn < 0.0f) {
            zoid->steer = -zoid->steer;
        }
        zoid->field_1C90[0] = turn;
    }
}
