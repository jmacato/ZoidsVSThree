#include "zoid3.h"

extern f32 sLiner(f32 target, f32 current, f32 fraction);
extern f32 sRotLinear(f32 target, f32 current, f32 fraction);

void ZoidLinerAnimXor(HSD_JObj *joint, JointPose *pose, f32 fraction, ZoidState *zoid)
{
    s32 index;
    s32 row;
    s32 col;

    if (joint == (void *)0) {
        return;
    }
    if (pose == (void *)0) {
        return;
    }
    for (index = 0; index < 10; index++) {
        if (zoid->attack_objects[index].joint == joint) {
            return;
        }
    }
    if (zoid->spik_joints[5] == joint) {
        return;
    }
    joint->translation.x = sLiner(joint->translation.x, pose->translation.x, fraction);
    joint->translation.y = sLiner(joint->translation.y, pose->translation.y, fraction);
    joint->translation.z = sLiner(joint->translation.z, pose->translation.z, fraction);
    joint->rotation[0] = sRotLinear(joint->rotation[0], pose->rotation[0], fraction);
    joint->rotation[1] = sRotLinear(joint->rotation[1], pose->rotation[1], fraction);
    joint->rotation[2] = sRotLinear(joint->rotation[2], pose->rotation[2], fraction);
    joint->scale.x = sLiner(joint->scale.x, pose->scale.x, fraction);
    joint->scale.y = sLiner(joint->scale.y, pose->scale.y, fraction);
    joint->scale.z = sLiner(joint->scale.z, pose->scale.z, fraction);
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 4; col++) {
            joint->matrix[row][col] = sLiner(joint->matrix[row][col], pose->matrix[row][col], fraction);
        }
    }
    if (joint->flags & 0x1000) {
        return;
    }
    joint = joint->child;
    pose = pose->child;
    while (joint != 0) {
        if (joint == (void *)0 || pose == (void *)0) {
            return;
        }
        ZoidLinerAnimXor(joint, pose, fraction, zoid);
        joint = joint->next;
        pose = pose->next;
    }
}
