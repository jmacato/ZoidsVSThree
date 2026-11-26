#include "zoid3.h"

extern JointPose *zdSearchBAK(HSD_JObj *joint, JointPose *pose, HSD_JObj *target);
extern void ZoidCopyAnim1(HSD_JObj *joint, JointPose *pose);

void zdLinierReset(ZoidState *zoid, HSD_JObj *joint)
{
    JointPose *pose;
    JointPose *search_pose;
    HSD_JObj *search_joint;
    if (joint != (void *)0) {
        search_pose = zoid->pose;
        search_joint = zoid->joint;
        pose = zdSearchBAK(search_joint, search_pose, joint);
        if (pose != (void *)0)
            ZoidCopyAnim1(joint, pose);
    }
}
