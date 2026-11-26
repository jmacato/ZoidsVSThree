#include "zoid3.h"

extern HSD_JObj *jobjWithAobj(HSD_JObj *joint);
extern JointPose *stSearchJobj(HSD_JObj *joint, JointPose *pose, HSD_JObj *target);

s32 zdGetAnimNum(ZoidState *zoid, HSD_JObj *joint)
{
    JointPose *pose;
    joint = jobjWithAobj(joint);
    pose = stSearchJobj(zoid->joint, zoid->pose, joint);
    if (pose == (void *)0)
        return -1;
    return pose->animation_index;
}
