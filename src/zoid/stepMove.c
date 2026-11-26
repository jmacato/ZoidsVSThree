#include "zoid3.h"

extern void angLimit(f32 *angle);

void stepMove(ZoidState *zoid)
{
    ZoidAIState *ai;
    union {
        f32 f;
        u32 u;
    } rate;
    union {
        f32 f;
        u32 u;
    } mag;
    f32 limit;
    f32 step;

    ai = zoid->ai;
    if (ai != 0 && ai->mode == 0) {
        ai = 0;
    }
    if (ai != 0 && zoid->ai_active != 0) {
        return;
    }
    rate.f = zoid->field_1C74;
    rate.u &= 0x7FFFFFFF;
    if (rate.f < 0.6) {
        zoid->field_1DBC &= 0xFFFFFFFE;
    }
    if (zoid->field_1DBC & 1) {
        return;
    }
    if (zoid->action_phase == 0) {
        return;
    }
    step = (f32)(4.0 * -(2.0 * (3.1415926 * zoid->field_1C74) / 360.0));
    limit = (f32)(0.1 * zoid->field_1C84);
    mag.f = step;
    mag.u &= 0x7FFFFFFF;
    if (mag.f > limit) {
        if (step > 0.0f) {
            step = limit;
        } else {
            step = -limit;
        }
    }
    zoid->heading += step;
    angLimit(&zoid->heading);
}
