#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"

typedef struct ParabolaCamera {
    u8 pad_000[0x588];
    s32 target_marker_count;
} ParabolaCamera;

typedef struct ParabolaWeapon {
    s32 active;
    u8 pad_04[8];
    s32 field_0C;
    ModelArchive *archive;
    s32 field_14;
    u8 pad_18[0x24];
    ZoidState *owner;
} ParabolaWeapon;

extern ModelArchive *dsp1p;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 sCameraPt2d(ParabolaCamera *camera, Vec3 *position, s32 *screen_point);
extern s32 sCameraJobjPt2d(ParabolaCamera *camera, HSD_JObj *joint, s32 *screen_point);
extern s32 sWeaponGetBarrelParabola(ParabolaWeapon *weapon, Vec3 *position, f32 distance);
extern HSD_JObj *grdObjGetJObj(s32 index);
extern void jobjDisp(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);
extern f64 __frsqrte(f64);

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

static inline f32 fabsf(f32 *value)
{
    return (*(u32 *)value &= 0x7FFFFFFF, *value);
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

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

void s1pWp1TgtParabola(ParabolaCamera *camera, ParabolaWeapon *weapon, f32 distance)
{
    register s32 i;
    HSD_JObj *jobj;
    HSD_JObj *target_joint;
    ZoidState *owner;
    HSD_JObj *normal;
    HSD_JObj *lock;
    ZoidState *target;
    f32 x;
    f32 y;
    f32 x2;
    f32 y2;
    s32 b;
    s32 a;
    Vec3 position;
    f32 tpos[3];
    s32 pt[2];
    s32 pt2[2];
    s32 slot;
    volatile f32 root;
    f32 diff;
    f32 dx2;
    f32 dy2;

    (void)target;
        if (dsp1p == 0)
        return;
    if (weapon == (void *)0)
        return;
    if (weapon->active == 0)
        return;
    owner = weapon->owner;
    target_joint = 0;
    b = weapon->field_14;
    a = weapon->field_0C;
    if (owner != 0) {
        if (owner->target_pending != 0) {
            if ((target = &Zoid[owner->target_slot]) != 0)
                target_joint = (HSD_JObj *)target->camera_joint;
        }
        if (owner->lock_active != 0)
            target_joint = grdObjGetJObj(owner->lock_obj);
    }
    if (target_joint != 0) {
        for (i = 0; i < 3; i++)
            tpos[i] = target_joint->matrix[i][3];
        x = tpos[0] - weapon->archive->models[0]->matrix[0][3];
        y = tpos[2] - weapon->archive->models[0]->matrix[2][3];
        distance = sqrtf(x * x + y * y, &root);
    }
    slot = *(s32 *)((u8 *)weapon->archive + (weapon->field_14 << 2) + 0x3c);
    if (sWeaponGetBarrelParabola(weapon, &position, distance) == 0)
        return;
    if (sCameraPt2d(camera, &position, pt) == 0)
        return;
    normal = GetChild(dsp1p->models[14], 0, 3, -1, -1, -1);
    lock = GetChild(dsp1p->models[14], 0, 1, -1, -1, -1);
    x = (pt[0] - 320) / 10.0;
    y = (240 - pt[1]) / 10.0;
    jobj = normal;
    if (target_joint != 0) {
        for (i = 0; i < 3; i++) {
            diff = target_joint->matrix[i][3] - (&position.x)[i];
            if (fabsf(&diff) > 12.0f)
                break;
        }
        if (i == 3)
            jobj = lock;
    }
    if (target_joint != 0) {
        jobj = lock;
        if (sCameraJobjPt2d(camera, target_joint, pt2) == 0)
            return;
        x2 = (pt2[0] - 320) / 10.0;
        y2 = (240 - pt2[1]) / 10.0;
        dx2 = x - x2;
        if (fabsf(&dx2) > 1.0f)
            jobj = normal;
        dy2 = y - y2;
        if (fabsf(&dy2) > 1.0f)
            jobj = normal;
    }
    if (jobj == lock)
        camera->target_marker_count++;
    HSD_JObjSetTranslateX(jobj, x);
    HSD_JObjSetTranslateY(jobj, y);
    jobjDisp(jobj);
}
