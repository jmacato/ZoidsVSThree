#pragma readonly_strings on
#include "zoid3.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void sLinier3d(f32 *current, f32 *target, f32 fraction);

#pragma auto_inline off
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

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetScaleY(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 819, "jobj");
    jobj->scale.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetScaleZ(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 833, "jobj");
    jobj->scale.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void ZoidToF(ZoidLimb *limb, ZoidLimb *target, f32 rate)
{
    HSD_JObj *joint;
    HSD_JObj *target_joint;
    f32 *to;
    f32 *from;
    s32 i;

    if (limb == (void *)0) {
        return;
    }
    if (target == (void *)0) {
        return;
    }
    joint = limb->joint;
    target_joint = target->joint;
    if (joint == (void *)0) {
        return;
    }
    if (target_joint == (void *)0) {
        return;
    }
    from = (f32 *)target;
    to = (f32 *)limb;
    sLinier3d(to, from, rate);
    for (i = 0; i < 3; i++) {
        joint->matrix[i][3] = to[i];
    }
    sGlobal2Local(joint);
    HSD_JObjSetScaleX(joint, 1.0f);
    HSD_JObjSetScaleY(joint, 1.0f);
    HSD_JObjSetScaleZ(joint, 1.0f);
}
