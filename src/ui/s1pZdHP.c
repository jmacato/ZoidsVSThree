#pragma readonly_strings on
#include "zoid3.h"
#include "game_camera.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

typedef struct S1pDisplay {
    u8 reserved_00[0x40];
    HSD_JObj *hp_joint;
    HSD_JObj *hp_joint_half;
    u8 reserved_48[0x88 - 0x48];
    HSD_JObj *hp_joint_alt;
} S1pDisplay;

extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPosS(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 a, s32 b, s32 c);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern s32 sCamNN;
extern s32 sCamNS;
extern void __assert(const char *file, s32 line, const char *expr);

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void s1pZdHP(CameraState *camera, ZoidState *zoid, S1pDisplay *display, HSD_JObj *parent)
{
    HSD_JObj *child;
    HSD_JObj *bar;
    HSD_JObj *target;
    f32 ratio;
    s32 danger;

    if (parent != 0) {
        child = GetChild(parent, 0, 1, -1, -1, -1);
        if (child != 0) {
            target = display->hp_joint;
            if (sCamNN == 2 && sCamNS == 1 && camera->half == 1) {
                target = display->hp_joint_half;
            }
            if (sCamNN == 4) {
                target = display->hp_joint_alt;
            }
            if (target != 0) {
                jobjCopyPosS(child, target);
                if (zoid->max_health <= 0) {
                    zoid->max_health = 100;
                }
                ratio = (f32)zoid->health / (f32)zoid->max_health;
                if (ratio < 0.3) {
                    danger = 1;
                } else {
                    danger = 0;
                }
                HSD_JObjDisp(GetChild(target, 0, danger, -1, -1, -1), 0, 7, 0);
                bar = GetChild(target, 0, danger, 0, -1, -1);
                HSD_JObjSetScaleX(bar, ratio);
                HSD_JObjDisp(bar, 0, 7, 0);
                HSD_JObjDisp(GetChild(target, 0, danger, 1, -1, -1), 0, 7, 0);
            }
        }
    }
}
