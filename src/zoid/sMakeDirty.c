#pragma readonly_strings on
#include "joint.h"

extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *condition);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

void sMakeDirty(HSD_JObj *jobj)
{
    if (jobj == (void *)0) {
        return;
    }
    if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
    jobj = jobj->child;
    while (jobj != 0) {
        sMakeDirty(jobj);
        jobj = jobj->next;
    }
}
