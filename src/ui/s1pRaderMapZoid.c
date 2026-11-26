#include "zoid3.h"
#include "game_camera.h"
#include "model_archive.h"
#include "matrix.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USE_QUATERNION 0x20000

extern ModelArchive *dspRader;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPosS(HSD_JObj *source, HSD_JObj *target);
extern struct HSD_TObj *searchTObjN(HSD_JObj *joint, s32 *index);
extern void texScrollMtx(struct HSD_TObj *tobj, Mtx matrix);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);
extern ModelArchive *dspPoint;
typedef struct StageInfo3 {
    u8 reserved_00[6];
    s16 radar_length;
    u8 reserved_08[0x58];
} StageInfo3;
extern StageInfo3 Stg;
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *condition);

#pragma readonly_strings on
#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x800000) && (jobj->flags & 0x40);
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

void s1pRaderMapZoid(ZoidState *zoid, s32 kind, HSD_JObj *joint)
{
    HSD_JObj *point;
    f32 scale;
    f32 dx;
    f32 dy;
    f32 rotation;
    f32 x;
    f32 z;
    HSD_JObj *child;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    if (zoid->death_started != 0)
        return;
    if (zoid->option_active == 2)
        return;
    if (dspRader == NULL)
        return;
    child = GetChild(dspRader->models[0], 0, 1, -1, -1, -1);
    scale = HSD_JObjGetScaleX(joint);
    point = GetChild(dspPoint->models[0], 0, kind, -1, -1, -1);
    jobjCopyPos(child, point);
    x = zoid->position[0];
    z = zoid->position[2];
    if (point == NULL)
        return;
    dx = scale * (12.8 * (x / Stg.radar_length));
    HSD_JObjAddTranslationX(point, dx);
    dy = scale * (12.8 * (-z / Stg.radar_length));
    HSD_JObjAddTranslationY(point, dy);
    rotation = 3.1415926 + zoid->heading;
    HSD_JObjSetRotationZ(point, rotation);
    HSD_JObjDisp(point, 0, 7, 0);
}
