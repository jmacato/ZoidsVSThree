#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"

typedef struct StraightCamera {
    u8 pad_000[0x588];
    s32 target_marker_count;
} StraightCamera;

typedef struct StraightMarker {
    f32 position[3];
    s32 locked;
    u8 pad_10[4];
    ZoidState *target;
} StraightMarker;

typedef struct StraightWeapon {
    s32 active;
    u8 pad_04[8];
    s32 field_0C;
    s32 *table;
    s32 field_14;
    u8 pad_18[0x24];
    ZoidState *owner;
    u8 pad_40[0x3B0];
    f32 range;
    u8 pad_3F4[0x18];
    StraightMarker markers[1];
} StraightWeapon;

extern ModelArchive *dsp1p;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 sCameraPt2d(StraightCamera *camera, Vec3 *position, s32 *screen_point);
extern s32 sCameraJobjPt2d(StraightCamera *camera, HSD_JObj *joint, s32 *screen_point);
extern s32 sWeaponGetBarrel(StraightWeapon *weapon, Vec3 *position, f32 distance);
extern HSD_JObj *grdObjGetJObj(s32 index);
extern void jobjDisp(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);

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

void s1pWp1TgtStraight(StraightCamera *camera, StraightWeapon *weapon, f32 distance)
{
    HSD_JObj *normal;
    ZoidState *target;
    HSD_JObj *lock;
    HSD_JObj *jobj;
    HSD_JObj *target_joint;
    StraightMarker *marker;
    ZoidState *owner;
    s32 i;
    s32 b;
    s32 a;
    Vec3 position;
    s32 pt[2];
    s32 pt2[2];
    s32 slot;
    f32 diff;
    f32 dx;
    f32 dy;
    f32 x;
    f32 y;
    f32 x2;
    f32 y2;

    if (dsp1p == 0)
        return;
    if (weapon == (void *)0)
        return;
    if (weapon->active == 0)
        return;
    marker = &weapon->markers[0];
    marker->target = 0;
    target_joint = 0;
    target = 0;
    owner = weapon->owner;
    b = weapon->field_14;
    a = weapon->field_0C;
    if (owner->target_pending != 0) {
        if ((target = &Zoid[owner->target_slot]) != 0)
            target_joint = (HSD_JObj *)target->camera_joint;
    }
    if (owner->lock_active != 0)
        target_joint = grdObjGetJObj(owner->lock_obj);
    slot = *(s32 *)((u8 *)weapon->table + (weapon->field_14 << 2) + 0x3c);
    if (sWeaponGetBarrel(weapon, &position, distance) == 0)
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
        dx = x - x2;
        if (fabsf(&dx) > 1.0f)
            jobj = normal;
        dy = y - y2;
        if (fabsf(&dy) > 1.0f)
            jobj = normal;
    }
    if (weapon->range < distance)
        jobj = normal;
    if (jobj == lock) {
        camera->target_marker_count++;
        marker->target = target;
    }
    HSD_JObjSetTranslateX(jobj, x);
    HSD_JObjSetTranslateY(jobj, y);
    jobjDisp(jobj);
}
