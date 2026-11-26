#include "zoid3.h"
#include "angle.h"

typedef struct Missile3 {
    u32 flags;
    u8 reserved_04[0x0C - 0x04];
    s32 kind;
    u8 reserved_10[0x24 - 0x10];
    HSD_JObj *joint;
    u8 reserved_28[0x30 - 0x28];
    ZoidState *target_zoid;
    u8 reserved_34[0x3C - 0x34];
    void *field_3C;
    u8 reserved_40[0x58 - 0x40];
    f32 matrix[3][4];
    u8 reserved_88[0xF4 - 0x88];
    s32 purge_timer;
    s32 hit;
    u8 reserved_FC[0x1A4 - 0xFC];
} Missile3;

extern Missile3 missileStart[200];
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);
extern f64 __frsqrte(f64 value);

static inline f32 sqrtf(f32 x, volatile f32 *y)
{
    if (x > 0.0f) {
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        *y = x * guess;
        return *y;
    }
    return x;
}

f32 sMisZdAng(ZoidState *zoid, f32 *angle)
{
    Missile3 *missile;
    Missile3 *best;
    ZoidState *target;
    f32 nearest;
    f32 length;
    f32 delta;
    f32 sum;
    f32 result;
    s32 i;
    s32 k;
    Vec3 point;
    volatile f32 root;

    nearest = -1.0f;
    best = 0;
    if (zoid == (void *)0)
        return nearest;
    if (zoid->joint == (void *)0)
        return nearest;
    missile = missileStart;
    for (i = 0; i < 200; i++, missile++) {
        if (!(missile->flags & 1))
            continue;
        if (missile->purge_timer != 0)
            continue;
        if (missile->kind != 6 && missile->hit != 0)
            continue;
        if (missile->joint == (void *)0)
            continue;
        if (missile->field_3C != (void *)0)
            continue;
        target = missile->target_zoid;
        if (missile->kind != 6) {
            if (target == (void *)0)
                continue;
            if (target->joint == (void *)0)
                continue;
            if (target != zoid)
                continue;
        }
        sum = 0.0f;
        for (k = 0; k < 3; k++) {
            delta = zoid->position[k] - missile->matrix[k][3];
            sum += delta * delta;
        }
        length = sqrtf(sum, &root);
        if (nearest > length || nearest == -1.0f) {
            nearest = length;
            best = missile;
        }
    }
    if (angle == (void *)0 || best == (void *)0 || nearest == -1.0f)
        return nearest;
    for (k = 0; k < 3; k++)
        (&point.x)[k] = best->joint->matrix[k][3];
    result = ZoidCalcAngle(zoid, &point);
    *angle = result;
    return nearest;
}
