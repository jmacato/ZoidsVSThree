#pragma readonly_strings on
#include "zoid3.h"

#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY);
}

void ik3dF(ZoidState *zoid, FootJoint *foot)
{
    HSD_JObj *joint;
    f32 limit;

    if (zoid == 0) {
        return;
    }
    if (foot == 0) {
        return;
    }
    joint = foot->joint;
    if (joint == 0) {
        return;
    }
    if (foot->no_contact_frames == 0) {
        return;
    }
    limit = foot->offset + foot->ground;
    joint->matrix[1][3] = limit;
    sGlobal2Local(joint);
    if (joint != 0 && !HSD_JObjMtxIsDirty(joint)) {
        HSD_JObjSetMtxDirtySub(joint);
    }
    sMakeMatrix(joint);
    limit = joint->matrix[1][3] - foot->offset - 0.1;
    if (foot->ground >= limit) {
        foot->flags |= 3;
    }
}
