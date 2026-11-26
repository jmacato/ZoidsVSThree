#include "joint.h"

extern void __assert(const char *file, s32 line, const char *expr);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *joint);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

void sMakeMatrix(HSD_JObj *joint)
{
    if (joint != (void *)0) {
        if (joint != 0 && HSD_JObjMtxIsDirty(joint))
            HSD_JObjSetupMatrixSub(joint);
        for (joint = joint->child; joint != 0; joint = joint->next)
            sMakeMatrix(joint);
    }
}
