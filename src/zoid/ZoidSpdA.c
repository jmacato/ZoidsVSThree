#include "zoid3.h"

extern f64 __frsqrte(f64);

static inline f32 sqrtf(f32 x)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;
    volatile f32 y;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

void ZoidSpdA(ZoidState *zoid)
{
    f32 sum;
    f32 value;
    f64 scale;
    s32 i;

    if (zoid != 0 && zoid->joint != 0) {
        sum = 0.0f;
        for (i = 0; i < 3; i++) {
            zoid->previous_displacement[i] = zoid->displacement[i];
            zoid->displacement[i] = zoid->position[i] - zoid->field_1C24[i];
            value = zoid->displacement[i];
            sum = value * value + sum;
            zoid->displacement_change[i] = zoid->displacement[i] - zoid->previous_displacement[i];
        }
        zoid->speed = sqrtf(sum);
        if (zoid->field_1EB0 != 0 || zoid->field_1EB2 != 0) {
            for (i = 0; i < 3; i++) {
                zoid->displacement[i] = 0.0f;
            }
        }
    }
}
