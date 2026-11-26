#include "types.h"

extern void angLimit(f32 *value);

f32 sRotLinear(f32 value, f32 base, f32 scale)
{
    f32 delta;
    f32 result;

    delta = value - base;
    angLimit(&delta);
    result = delta * scale + base;
    angLimit(&result);
    return result;
}
