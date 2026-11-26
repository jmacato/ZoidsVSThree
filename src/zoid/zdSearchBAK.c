#include "zoid3.h"

JointPose *zdSearchBAK(HSD_JObj *joint, JointPose *pose, HSD_JObj *target)
{
    JointPose *found;

    if (joint == (void *)0) {
        return 0;
    }
    if (pose == (void *)0) {
        return 0;
    }
    if (joint == target) {
        return pose;
    }
    joint = joint ? joint->child : 0;
    pose = pose ? pose->child : 0;
    while (joint != 0) {
        found = zdSearchBAK(joint, pose, target);
        if (found != 0) {
            return found;
        }
        joint = joint ? joint->next : 0;
        pose = pose ? pose->next : 0;
    }
    return 0;
}
