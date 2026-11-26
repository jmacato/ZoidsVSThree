#include "zoid3.h"

#define JOBJ_MTX_INDEP_SRT 0x02000000

extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *condition);

#pragma readonly_strings on
#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

static inline void HSD_JObjSetTranslationX(HSD_JObj *jobj, f32 x)
{
    jobj ? (void)0 : __assert("jobj.h", 952, "jobj");
    jobj->translation.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetTranslationY(HSD_JObj *jobj, f32 y)
{
    jobj ? (void)0 : __assert("jobj.h", 966, "jobj");
    jobj->translation.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetTranslationZ(HSD_JObj *jobj, f32 z)
{
    jobj ? (void)0 : __assert("jobj.h", 980, "jobj");
    jobj->translation.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}

void zdChildAnmDif(ZoidState *zoid)
{
    HSD_JObj *joint;
    HSD_JObj *child;
    f32 *delta;
    s32 anim;

    if (zoid != 0 && (joint = zoid->joint, joint != 0) && (child = joint->child, child != 0)) {
        anim = zoid->current_animation;
        delta = zoid->child_translation_delta;
        if (anim >= 0x52 || anim < 0x43)
            return;
        HSD_JObjSetTranslationX(child, zoid->field_1A40[0] + delta[0]);
        HSD_JObjSetTranslationY(child, zoid->field_1A40[1] + delta[1]);
        HSD_JObjSetTranslationZ(child, zoid->field_1A40[2] + delta[2]);
    }
}
