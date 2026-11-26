#include "zoid3.h"
#include "zoid_collision.h"

#define JOBJ_HIDDEN 0x10

extern void HSD_JObjClearFlags(HSD_JObj *jobj, u32 flags);
extern void HSD_JObjSetFlags(HSD_JObj *jobj, u32 flags);
extern void HSD_JObjDisp(HSD_JObj *jobj, void *mtx, u32 flags, u32 rendermode);

void zdCoSmallDisp(CoObj *co)
{
    HSD_JObj *joint;

    if (co == (void *)0) {
        return;
    }
    joint = co->joint;
    if (joint == (void *)0) {
        return;
    }
    HSD_JObjClearFlags(joint, JOBJ_HIDDEN);
    HSD_JObjDisp(joint, 0, 7, 0);
    HSD_JObjSetFlags(joint, JOBJ_HIDDEN);
}
