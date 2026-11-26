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

f32 zdCoCoMinR0(CoObj *a, CoObj *b, Vec3 *direction, s32 a_max, s32 b_max)
{
    HSD_JObj *ja;
    HSD_JObj *jb;
    f32 distance;
    f32 radius;
    f32 depth;
    f32 delta;
    s32 i;

    if (a == (void *)0) {
        return 0.0f;
    }
    if (b == (void *)0) {
        return 0.0f;
    }
    ja = *(HSD_JObj **)a;
    jb = *(HSD_JObj **)b;
    if (ja == (void *)0) {
        return 0.0f;
    }
    if (jb == (void *)0) {
        return 0.0f;
    }
    distance = 0.0f;
    for (i = 0; i < 3; i++) {
        delta = ja->matrix[i][3] - jb->matrix[i][3];
        distance += delta * delta;
        ((f32 *)direction)[i] = delta;
    }
    distance = sqrtf(distance);
    if (0.0f == distance) {
        return 0.0f;
    }
    radius = a->minimum_scale;
    if (a_max == 1) {
        radius = a->maximum_scale;
    }
    if (b_max == 0) {
        radius += b->minimum_scale;
    } else {
        radius += b->maximum_scale;
    }
    depth = radius - distance;
    if (depth <= 0.0f) {
        return 0.0f;
    }
    for (i = 0; i < 3; i++) {
        ((f32 *)direction)[i] = ((f32 *)direction)[i] * depth / distance;
    }
    return depth;
}
