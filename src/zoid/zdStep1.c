#include "zoid3.h"

extern void zdStep0f(ZoidState *zoid, f32 heading);

void zdStep1(ZoidState *zoid, s32 degrees)
{
    zdStep0f(zoid, (f32)(((2.0 * (3.1415926 * (f64)(f32)degrees)) / 360.0)));
}
