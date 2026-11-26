#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"

typedef struct RotInfo {
    u8 reserved_00[0x13];
    s8 team;
    u8 reserved_14;
    s8 enabled;
    s8 limit_lo;
    s8 limit_hi;
    u8 reserved_18;
    s8 yaw_speed;
    s8 pitch_speed;
    u8 reserved_1B[0x34 - 0x1B];
    u16 range;
} RotInfo;

typedef struct RotObject {
    u8 reserved_00[4];
    Vec3 position;
    u8 reserved_10[0x30];
    f32 mtx[3][4];
    u8 reserved_70[4];
    HSD_JObj *joint;
    s32 field_78;
    u8 reserved_7C[0x14];
    f32 yaw;
    f32 yaw_error;
    f32 pitch;
    f32 pitch_error;
    s32 target;
    f32 inverse[3][4];
    Vec3 local;
    RotInfo *info;
} RotObject;

extern s32 vsyncN;
extern f32 sLenPoint3d(Vec3 *first, Vec3 *second);
extern f32 calcAng1(Vec3 *point);
extern void sLinear1D(f32 *value, f32 target, f32 step);
extern void angLimit(f32 *angle);
extern f32 atan2f(f32 y, f32 x);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern u32 PSMTXInverse(f32 src[3][4], f32 dst[3][4]);
extern void PSMTXMultVec(f32 m[3][4], Vec3 *src, Vec3 *dst);
extern f64 __frsqrte(f64);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);

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

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != 0 && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetRotationX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 676, "jobj");
    !(jobj->flags & 0x20000) ? (void)0 : __assert("jobj.h", 677, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[0] = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 696, "jobj");
    !(jobj->flags & 0x20000) ? (void)0 : __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[1] = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

void grdObjRot(RotObject *object)
{
    s32 i;
    ZoidState *zoid;
    HSD_JObj *child;
    Vec3 *local;
    s32 best;
    RotInfo *info;
    f32 z;
    f32 x;
    f32 distance;
    f32 best_distance;
    f32 angle;
    f32 y;
    f32 len;
    f32 value;
    f32 value2;
    f32 pos[3];
    volatile f32 root;

    info = object->info;
    if (info == 0)
        return;
    if (object->field_78 != 0)
        return;
    best = -1;
    if ((vsyncN & 0x3F) == 0) {
        object->target = -1;
        for (i = 0; i < 16; i++) {
            zoid = &Zoid[i];
            if (zoid->joint == 0)
                continue;
            if (zoid->death_started != 0)
                continue;
            if (info->team == zoid->slot)
                continue;
            distance = sLenPoint3d(&object->position, (Vec3 *)zoid->position);
            if (distance > info->range)
                continue;
            if (best != -1 && !(distance < best_distance))
                continue;
            best = i;
            best_distance = distance;
        }
        object->target = best;
    }
    if (object->target == -1)
        return;
    zoid = &Zoid[object->target];
    if (zoid->joint == 0)
        return;
    if (zoid->death_started != 0)
        return;
    for (i = 0; i < 3; i++)
        pos[i] = zoid->joint->matrix[i][3];
    PSMTXInverse(object->joint->matrix, object->inverse);
    local = &object->local;
    PSMTXMultVec(object->mtx, (Vec3 *)pos, local);
    angle = calcAng1(local);
    if (-100.0f != angle) {
        value = object->yaw;
        sLinear1D(&value, angle, (f32)((s32)info->yaw_speed / 60.0) * 3.1415926 * 2.0 / 360.0);
        angLimit(&value);
        object->yaw = value;
        HSD_JObjSetRotationY(object->joint, value);
        value2 = angle - value;
        angLimit(&value2);
        object->yaw_error = value2;
    }
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    zoid = zoid;
    if (info->enabled == 0)
        return;
    if (!(child = GetChild(object->joint, 0, 0, 0, -1, -1))) {
        info->enabled = 0;
        return;
    }
    z = local->z;
    x = local->x;
    y = local->y;
    len = sqrtf(x * x + z * z, &root);
    if (0.0f == y && 0.0f == len)
        return;
    angle = -atan2f(y, len);
    value = object->pitch;
    sLinear1D(&value, angle, (f32)((s32)info->pitch_speed / 60.0) * 3.1415926 * 2.0 / 360.0);
    angLimit(&value);
    z = -((f32)(s32)info->limit_lo * 3.1415926 * 2.0 / 360.0);
    if (value < z)
        value = z;
    z = (f32)(s32)info->limit_hi * 3.1415926 * 2.0 / 360.0;
    if (value > z)
        value = z;
    object->pitch = value;
    HSD_JObjSetRotationX(child, value);
    value2 = angle - value;
    angLimit(&value2);
    object->pitch_error = value2;
}
