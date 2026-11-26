#include "zoid3.h"
#include "missile.h"

void zdEffectMount(ZoidState *zoid, s32 mount, s32 effect)
{
    HSD_JObj *joint;
    s32 mode;
    s32 kind;

    if (effect <= 0) {
        return;
    }
    if (zoid == 0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    if (mount > 27) {
        return;
    }
    if (effect >= 0x88) {
        return;
    }
    joint = zoid->joint;
    kind = Tea_effectdat[effect].kind;
    mode = 2;
    if (joint == 0) {
        return;
    }
    if (kind == EFFECT_KIND_ZOID) {
        mode = 3;
        mount = -1;
    }
    if (mount < 0) {
        mount = -1;
    }
    if (mount > 27) {
        mount = 27;
    }
    switch (mount) {
    case -1:
        joint = zoid->joint;
        break;
    case 27:
        joint = zoid->joint->child;
        break;
    default:
        joint = zoid->weapon_slots[mount].joint;
        break;
    }
    if (joint == 0) {
        return;
    }
    sEffectSet(effect, mode, 0, joint, zoid);
}
