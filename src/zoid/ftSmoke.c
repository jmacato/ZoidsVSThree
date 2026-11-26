#include "zoid3.h"
#include "missile.h"

void ftSmoke(ZoidState *zoid, FootJoint *foot, s32 frame)
{
    HSD_JObj *joint;
    u32 flags;

    if (zoid == (void *)0) {
        return;
    }
    if (foot == (void *)0) {
        return;
    }
    joint = foot->joint;
    if (joint == (void *)0) {
        return;
    }
    flags = foot->flags;
    if ((flags & FOOT_FLAG_CONTACT) && !(flags & FOOT_FLAG_PREVIOUS_CONTACT) && frame > 3) {
        sEffectSet(56, 1, 0, joint, 0);
    }
    if (flags & FOOT_FLAG_CONTACT) {
        flags |= FOOT_FLAG_PREVIOUS_CONTACT;
    } else {
        flags &= ~FOOT_FLAG_PREVIOUS_CONTACT;
    }
    foot->flags = flags;
}
