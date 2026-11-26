#include "zoid3.h"

#define JOBJ_INSTANCE 0x1000

#pragma dont_inline on

void ZoidCopyAnim1(HSD_JObj *joint, JointPose *pose)
{
    s32 row, column;
    if (joint != (void *)0 && pose != (void *)0) {
        pose->rotation[0] = joint->rotation[0];
        pose->rotation[1] = joint->rotation[1];
        pose->rotation[2] = joint->rotation[2];
        pose->translation.x = joint->translation.x;
        pose->translation.y = joint->translation.y;
        pose->translation.z = joint->translation.z;
        pose->scale.x = joint->scale.x;
        pose->scale.y = joint->scale.y;
        pose->scale.z = joint->scale.z;
        for (row = 0; row < 3; row++) {
            for (column = 0; column < 4; column++) {
                pose->matrix[row][column] = joint->matrix[row][column];
            }
        }
        if ((joint->flags & JOBJ_INSTANCE) != 0)
            return;
        joint = joint->child;
        pose = pose->child;
        while (joint != 0) {
            if (joint == (void *)0 || pose == (void *)0)
                return;
            ZoidCopyAnim1(joint, pose);
            joint = joint->next;
            pose = pose->next;
        }
    }
}
