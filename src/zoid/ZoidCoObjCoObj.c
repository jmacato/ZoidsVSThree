#include "zoid3.h"

typedef struct CoObj3 {
    HSD_JObj *joint;
    HSD_JObj *base_joint;
    u8 reserved_08[0x14 - 0x08];
    u32 object_contact;
    u8 reserved_18[0x38 - 0x18];
    f32 inverse[3][4];
} CoObj3;

extern f64 __frsqrte(f64);
extern s32 sTouchCube(HSD_JObj *a, HSD_JObj *b);
extern s32 sChkCubeInCube(f32 matrix[3][4], f32 inverse[3][4]);
extern s32 PSMTXInverse(f32 src[3][4], f32 inv[3][4]);
extern void sGlobal2Local(HSD_JObj *joint);

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

s32 ZoidCoObjCoObj(CoObj3 *a, CoObj3 *b, s32 flags)
{
    f32 pa[3];
    f32 pb[3];
    f32 mid[3];
    f32 d[3];
    f32 s[3];
    f32 len;
    s32 i;
    s32 k;

    if (a == (void *)0)
        return 0;
    if (b == (void *)0)
        return 0;
    if (a->joint == (void *)0)
        return 0;
    if (b->joint == (void *)0)
        return 0;
    if (sTouchCube(a->joint, b->joint) == 0)
        return 0;
    if (sChkCubeInCube(a->joint->matrix, b->inverse) == 0 && sChkCubeInCube(b->joint->matrix, a->inverse) == 0)
        return 0;
    if (a->base_joint == (void *)0)
        return 1;
    if (b->base_joint == (void *)0)
        return 1;
    len = 0.0f;
    for (k = 0; k < 3; k++) {
        pa[k] = a->joint->matrix[k][3];
        pb[k] = b->joint->matrix[k][3];
        mid[k] = (pa[k] + pb[k]) / 2.0f;
        d[k] = pb[k] - pa[k];
        len += d[k] * d[k];
    }
    len = sqrtf(len) / 0.02;
    if (0.0f == len)
        return 1;
    if (flags == 0)
        return 1;
    a->object_contact |= 1;
    b->object_contact |= 1;
    for (i = 1; i < 20; i++) {
        for (k = 0; k < 3; k++) {
            s[k] = i * (d[k] / len);
            a->joint->matrix[k][3] = pa[k] - s[k];
            b->joint->matrix[k][3] = pb[k] + s[k];
        }
        PSMTXInverse(a->joint->matrix, a->inverse);
        PSMTXInverse(b->joint->matrix, b->inverse);
        if (sChkCubeInCube(a->joint->matrix, b->inverse) == 0 && sChkCubeInCube(b->joint->matrix, a->inverse) == 0)
            break;
    }
    for (k = 0; k < 3; k++) {
        a->base_joint->matrix[k][3] -= s[k];
        b->base_joint->matrix[k][3] += s[k];
    }
    sGlobal2Local(a->base_joint);
    sGlobal2Local(b->base_joint);
    return 1;
}
