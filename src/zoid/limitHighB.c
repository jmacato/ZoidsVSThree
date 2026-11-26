#include "zoid3.h"

typedef union FloatBits {
    f32 f;
    u32 u;
} FloatBits;

extern f32 cosf(f32 x);

f32 limitHighB(f32 value)
{
    FloatBits a;
    FloatBits b;
    f32 result;

    a.f = value;
    a.u = a.u & 0x7FFFFFFF;
    value = a.f;
    if (value > 30.0f) {
        value = 30.0f;
    }
    value = (f32)(3.1415926 * value / 30.0);
    result = (f32)(1.5707963 * ((cosf(value) - 1.0) / 2.0));
    b.f = result;
    b.u = b.u & 0x7FFFFFFF;
    return b.f;
}
