#include "zoid3.h"

extern f32 sLenPoint3dR2(f32 *vector);
extern f32 atan2f(f32 y, f32 x);
extern void angLimit(f32 *angle);
extern void sLinear1D(f32 *value, f32 target, f32 step);

void antiV3(ZoidState *zoid)
{
    f32 angle;
    f32 length;
    f32 limit;
    f32 x;
    f32 z;

    if (zoid->field_1CCC != 0) {
        length = sLenPoint3dR2(zoid->field_1CC0);
        limit = zoid->field_1CC0[1];
        if (!(limit > length) && length != 0.0f) {
            z = zoid->field_1CC0[2];
            x = zoid->field_1CC0[0];
            angle = atan2f(x, z);
            angLimit(&angle);
            sLinear1D(&zoid->heading, angle, 0.08726646f);
        }
    }
}
