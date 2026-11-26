#include "zoid3.h"

void zdChildAnmBak(ZoidState *zoid)
{
    HSD_JObj *joint;
    HSD_JObj *child;
    s32 i;

    if (zoid == 0) {
        return;
    }
    joint = zoid->joint;
    if (joint == 0) {
        return;
    }
    child = joint->child;
    if (child == 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        zoid->previous_child_translation[i] = zoid->child_translation[i];
    }
    zoid->child_translation[0] = child->translation.x;
    zoid->child_translation[1] = child->translation.y;
    zoid->child_translation[2] = child->translation.z;
    for (i = 0; i < 3; i++) {
        zoid->child_translation_delta[i] = zoid->child_translation[i] - zoid->previous_child_translation[i];
    }
}
