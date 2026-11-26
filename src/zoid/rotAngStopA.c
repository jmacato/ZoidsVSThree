#include "zoid3.h"

extern void angLimit(f32 *angle);

void rotAngStopA(ZoidState *zoid, f32 angle)
{
    f32 diff;
    f32 absval;
    f32 step;

    if (zoid->target_pending != 0 || zoid->lock_active != 0) {
        step = 1.5 * (0.1 * zoid->field_1C84);
    } else {
        step = 0.1 * zoid->field_1C84;
    }
    diff = angle - zoid->heading;
    angLimit(&diff);
    if (0.0f != diff) {
        absval = diff;
        *(u32 *)&absval &= 0x7FFFFFFF;
        if (absval <= step) {
            zoid->heading = angle;
        } else {
            if (diff > 0.0f) {
                zoid->heading += step;
            } else {
                zoid->heading -= step;
            }
            angLimit(&zoid->heading);
        }
    }
}
