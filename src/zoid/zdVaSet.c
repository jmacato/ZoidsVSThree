#include "zoid3.h"

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

extern f32 sinf(f32 angle);
extern void angLimit(f32 *angle);

typedef struct ZoidControlSpan {
    u8 pad[0x98];
    s32 max_senter_roll;
} ZoidControlSpan;

void zdVaSet(ZoidState *zoid)
{
    ZoidControlSpan *control;
    f32 speed;
    f32 target;
    f32 current;
    f32 difference;
    f32 step = 2.0 * 3.1415926 * 2.0 / 360.0;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        speed = zoid->field_1C54;
        control = (ZoidControlSpan *)zoid->anim_data;
        if (speed > 1.0f) {
            speed = 1.0f;
        }
        difference = zoid->step_heading - zoid->heading;
        target = speed * sinf(difference);
        angLimit(&target);
        if (target < DEG((f32)-control->max_senter_roll)) {
            target = DEG((f32)-control->max_senter_roll);
        }
        if (target > DEG((f32)control->max_senter_roll)) {
            target = DEG((f32)control->max_senter_roll);
        }
        current = zoid->senter_roll;
        if (target > current) {
            current += step;
            if (target < current) {
                current = target;
            }
        }
        if (target < current) {
            current -= step;
            if (target > current) {
                current = target;
            }
        }
        zoid->senter_roll = current;
    }
}
