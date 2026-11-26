#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        *y = (f32)(x * guess);
        return *y;
    }
    return x;
}

f32 zdAI_lenPoint(s32 index, f32 x, f32 z)
{
    ZoidState *zoid;
    volatile f32 root;

    aiCmdReport("aiCmd-lenPoint \n");
    if (index < 0) {
        return 0.0f;
    }
    if (index >= 16) {
        return 0.0f;
    }
    zoid = &Zoid[index];
    x = x - zoid->position[0];
    z = z - zoid->position[2];
    return sqrtf(x * x + z * z, &root);
}
