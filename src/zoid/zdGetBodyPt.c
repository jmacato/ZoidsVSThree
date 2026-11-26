#include "zoid3.h"

void zdGetBodyPt(ZoidState *zoid, Vec3 *point)
{
    HSD_JObj *joint;
    s32 i;

    for (i = 0; i < 3; i++) {
        ((f32 *)point)[i] = zoid->position[i];
    }
    joint = zoid->buckle_joint;
    if (joint == (void *)0) {
        joint = *(HSD_JObj **)zoid->bust_coobj;
    }
    if (joint == (void *)0) {
        joint = *(HSD_JObj **)zoid->hip_coobj;
    }
    if (joint == (void *)0) {
        joint = *(HSD_JObj **)zoid->body_coobj;
    }
    if (joint == (void *)0) {
        joint = *(HSD_JObj **)zoid->bust_coobj;
    }
    if (joint == (void *)0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        ((f32 *)point)[i] = joint->matrix[i][3];
    }
}
