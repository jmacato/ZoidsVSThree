#pragma readonly_strings on
#pragma auto_inline off
#include "zoid3.h"
#include "model_archive.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USE_QUATERNION 0x20000

typedef struct RaderCamera {
    u8 pad_000[0x1C4];
    ZoidState *zoid;
    u8 pad_1C8[0x260 - 0x1C8];
    f32 yaw;
} RaderCamera;

extern ModelArchive *dspRader;
extern ModelArchive *dspPoint;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *condition);
extern void sMakeMatrix(HSD_JObj *joint);
extern void sCameraRela(RaderCamera *camera, Vec3 *point, Vec3 *out);
extern f64 __frsqrte(f64);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline f32 HSD_JObjGetScaleX(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 899, "jobj");
    return jobj->scale.x;
}

static inline void HSD_JObjAddTranslationX(HSD_JObj *jobj, f32 x)
{
    jobj ? (void)0 : __assert("jobj.h", 1109, "jobj");
    jobj->translation.x += x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjAddTranslationY(HSD_JObj *jobj, f32 y)
{
    jobj ? (void)0 : __assert("jobj.h", 1120, "jobj");
    jobj->translation.y += y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, f32 z)
{
    jobj ? (void)0 : __assert("jobj.h", 716, "jobj");
    !(jobj->flags & JOBJ_USE_QUATERNION) ? (void)0 : __assert("jobj.h", 717, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[2] = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

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

void s1pRaderBattleZoid(RaderCamera *camera, ZoidState *zoid, s32 kind, HSD_JObj *base)
{
    ZoidState *target;
    HSD_JObj *child;
    HSD_JObj *point;
    HSD_JObj *joint;
    Vec3 rel;
    Vec3 pos;
    f32 scale;
    f32 len;
    f32 range;
    f32 x;
    volatile f32 root;
    f32 z;
    f32 angle;
    s32 i;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    if (zoid->death_started != 0)
        return;
    if (kind != 0 && zoid->option_active == 2)
        return;
    target = camera->zoid;
    if (target == (void *)0)
        return;
    if (target->joint == (void *)0)
        return;
    if (dspPoint == 0)
        return;
    if (dspRader == 0)
        return;
    child = GetChild(dspRader->models[0], 0, 1, -1, -1, -1);
    point = GetChild(dspPoint->models[0], 0, kind, -1, -1, -1);
    scale = HSD_JObjGetScaleX(base);
    jobjCopyPos(child, point);
    sMakeMatrix(point);
    joint = *(HSD_JObj **)zoid->head_coobj;
    if (joint == NULL)
        joint = *(HSD_JObj **)zoid->bust_coobj;
    if (joint == NULL)
        joint = *(HSD_JObj **)zoid->neck_coobj;
    if (joint == NULL)
        joint = *(HSD_JObj **)zoid->hip_coobj;
    if (joint == NULL)
        joint = zoid->buckle_joint;
    if (joint == NULL)
        joint = zoid->joint;
    for (i = 0; i < 3; i++) {
        (&pos.x)[i] = joint->matrix[i][3];
    }
    sCameraRela(camera, &pos, &rel);
    z = rel.z;
    x = rel.x;
    len = sqrtf(x * x + z * z, &root);
    range = target->search_range;
    if (range < len)
        return;
    if (point == NULL)
        return;
    HSD_JObjAddTranslationX(point, scale * (12.8 * (x / range / 2.0f)));
    HSD_JObjAddTranslationY(point, scale * (12.8 * (z / range / 2.0f)));
    angle = zoid->heading - camera->yaw;
    HSD_JObjSetRotationZ(point, angle);
    HSD_JObjDisp(point, 0, 7, 0);
}
