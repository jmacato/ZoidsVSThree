#pragma readonly_strings on
#include "zoid3.h"

extern void sGlobal2Local(HSD_JObj *jobj);
extern HSD_JObj *grdObjGetJObj(s32 index);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
extern void __assert(const char *file, s32 line, const char *expr);

#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

void sZoidTarget(ZoidState *zoid)
{
    HSD_JObj *joint;
    HSD_JObj *local;
    ZoidState *other;
    s32 i;

    if (zoid->joint != (void *)0 && zoid->death_started == 0) {
        joint = 0;
        if (zoid->target_pending != 0) {
            if (zoid->target_slot == -1) {
                return;
            }
            other = &Zoid[zoid->target_slot];
            if (other->joint == (void *)0) {
                return;
            }
            if (other->death_started != 0) {
                return;
            }
            if (other->joint == 0) {
                return;
            }
            joint = other->joint;
        }
        if (zoid->lock_active != 0) {
            joint = grdObjGetJObj(zoid->lock_obj);
        }
        if (joint == (void *)0) {
            return;
        }
        if ((u32)other->camera_joint != 0) {
            joint = (HSD_JObj *)other->camera_joint;
        }
        local = zoid->field_1AE4;
        if (local == (void *)0) {
            return;
        }
        for (i = 0; i < 3; i++) {
            local->matrix[i][3] = joint->matrix[i][3];
        }
        sGlobal2Local(local);
        if (local != 0 && !HSD_JObjMtxIsDirty(local)) {
            HSD_JObjSetMtxDirtySub(local);
        }
        other = other;
    }
}
