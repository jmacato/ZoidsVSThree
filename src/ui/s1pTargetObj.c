#include "zoid3.h"
#include "game_camera.h"
#include "model_archive.h"

#pragma readonly_strings on

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);


#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY);
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

extern ModelArchive *dsp1p;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern HSD_JObj *grdObjGetJObj(s32 index);
extern void jobjDisp(HSD_JObj *joint);

void s1pTargetObj(CameraState *camera, ZoidState *zoid)
{
    HSD_JObj *child;
    HSD_JObj *target;
    s32 index;
    s32 i;
    s32 ok;
    s32 screen[2];
    f32 pos[3];
    f32 sx;
    f32 sy;
    s32 slot;

    if (dsp1p != 0) {
        slot = zoid->slot;
        child = GetChild(dsp1p->models[14], 0, 4, -1, -1, -1);
        if (zoid->lock_active != 0) {
            index = zoid->lock_obj;
            if (index >= 0) {
                target = grdObjGetJObj(index);
                if (target != 0) {
                    for (i = 0; i < 3; i++)
                        pos[i] = target->matrix[i][3];
                    ok = sCameraPt2d(camera, (Vec3 *)pos, screen);
                    if (ok != 0) {
                        sx = (screen[0] - 320) / 10.0;
                        sy = (240 - screen[1]) / 10.0;
                        HSD_JObjSetTranslateX(child, sx);
                        HSD_JObjSetTranslateY(child, sy);
                        jobjDisp(child);
                    }
                }
            }
        }
    }
}
