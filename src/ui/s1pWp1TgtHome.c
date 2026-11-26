#pragma auto_inline off
#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"

typedef struct HomeCamera {
    u8 pad_000[0x588];
    s32 target_marker_count;
} HomeCamera;

typedef struct HomeMarker {
    f32 position[3];
    s32 locked;
    u8 pad_10[4];
    ZoidState *target;
    void *source;
    HSD_JObj *joint;
    s32 field_20;
} HomeMarker;

typedef struct HomeWeapon {
    s32 active;
    u8 pad_04[8];
    s32 field_0C;
    u8 pad_10[4];
    s32 field_14;
    u8 pad_18[0x24];
    ZoidState *owner;
    u8 pad_40[0x3B0];
    f32 range;
    u8 pad_3F4[0xC];
    s32 marker_count;
    u8 pad_404[8];
    HomeMarker markers[1];
} HomeWeapon;

extern ModelArchive *dsp1p;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 sCameraPt2d(HomeCamera *camera, Vec3 *position, s32 *screen_point);
extern void jobjDisp(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *expr);

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

void s1pWp1TgtHome(HomeCamera *camera, HomeWeapon *weapon)
{
    HSD_JObj *normal;
    HSD_JObj *lock;
    HSD_JObj *jobj;
    HomeMarker *marker;
    ZoidState *target;
    void *source;
    s32 i;
    s32 b;
    s32 a;
    s32 pt[2];
    f32 x;
    f32 y;

    if (dsp1p == 0)
        return;
    if (weapon == (void *)0)
        return;
    if (weapon->active == 0)
        return;
    b = weapon->field_14;
    a = weapon->field_0C;
    normal = GetChild(dsp1p->models[14], 0, 0, -1, -1, -1);
    lock = GetChild(dsp1p->models[14], 0, 1, -1, -1, -1);
    for (i = 0; i < weapon->marker_count; i++) {
        marker = &weapon->markers[i];
        if (marker->joint == (void *)0)
            continue;
        target = marker->target;
        source = marker->source;
        if (target == 0 && source == 0 && marker->field_20 == -1)
            continue;
        if (target != 0 && target->joint != 0 && target->stel_state == 2) {
            marker->joint = 0;
            continue;
        }
        if (target != 0 && target->joint != 0 && weapon->owner != 0 && weapon->owner->distances[target->index] > weapon->range) {
            marker->joint = 0;
            continue;
        }
        if (sCameraPt2d(camera, (Vec3 *)marker, pt) == 0) {
            if (marker->locked != 0)
                marker->joint = 0;
            continue;
        }
        jobj = normal;
        if (marker->locked != 0) {
            camera->target_marker_count++;
            jobj = lock;
        }
        x = (pt[0] - 320) / 10.0;
        y = (240 - pt[1]) / 10.0;
        HSD_JObjSetTranslateX(jobj, x);
        HSD_JObjSetTranslateY(jobj, y);
        jobjDisp(jobj);
    }
}
