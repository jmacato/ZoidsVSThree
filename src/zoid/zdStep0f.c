#include "zoid3.h"
#include "angle.h"

extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void zdStep0f(ZoidState *zoid, f32 angle)
{
    s32 busy;
    ZoidControlData *control;
    f32 heading;
    f32 magnitude;
    f32 step;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        control = zoid->anim_data;
        if (control != 0) {
            if (zoid->action == 0x2a) return;
            if (zoid->action == 0x2b) return;
            if (zoid->requested_action >= 0x1b && zoid->requested_action <= 0x28) return;
            if (zoid->action >= 0x1b && zoid->action <= 0x28) return;
            busy = 0;
            if (zoid->action == 0x17) busy = 1;
            if (zoid->action == 0x18) busy = 1;
            if (zoid->action == 0x19) busy = 1;
            if (zoid->action == 0x1a) busy = 1;
            if (zoid->action == 0x2d) busy = 1;
            if (zoid->action == 0x2e) busy = 1;
            if (zoid->action == 0x2f) busy = 1;
            if (zoid->action == 0x30) busy = 1;
            if (zoid->action >= 0xd && zoid->action <= 0x16) busy = 1;
            if (zoid->jump_phase != 0) busy = 1;
            if (busy != 0) {
                zoid->requested_action = 0;
            } else {
                angLimit(&angle);
                heading = zoid->heading + angle;
                zoid->launch_velocity[0] = 0.8 * zoid->displacement[0] + sinf(heading);
                zoid->launch_velocity[2] = 0.8 * zoid->displacement[2] + cosf(heading);
                if (zoid->field_0170 != 0) {
                    step = (f32)control->step_launch_y / 40.0;
                    zoid->step_launch_x = step * sinf(heading);
                    zoid->step_launch_z = step * cosf(heading);
                    zoid->launch_velocity[0] = zoid->displacement[0];
                    zoid->launch_velocity[1] = 0.0f;
                    zoid->launch_velocity[2] = zoid->displacement[2];
                }
                if (zoid->field_0170 != 0) {
                    if (angle >= 0.0f && angle < DEG2RAD_D(45)) angle = 0.8028514385223389f;
                    if (angle <= 0.0f && angle > -DEG2RAD_D(45)) angle = -0.8028514385223389f;
                    if (angle > DEG2RAD_D(135)) angle = 2.3387410640716553f;
                    if (angle < -DEG2RAD_D(135)) angle = -2.3387410640716553f;
                }
                magnitude = absf(angle);
                zoid->requested_action = 0x2d;
                if (magnitude < DEG2RAD_D(45)) {
                    zoid->requested_action = 0x2d;
                } else if (magnitude > DEG2RAD_D(135)) {
                    zoid->requested_action = 0x2e;
                } else if (angle > 0.0f) {
                    zoid->requested_action = 0x30;
                } else {
                    zoid->requested_action = 0x2f;
                }
            }
        }
    }
}
