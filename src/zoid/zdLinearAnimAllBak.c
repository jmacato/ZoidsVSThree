#include "zoid3.h"

extern void zdLinearAnimAllBak1(HSD_JObj *joint, JointPose *pose);

void zdLinearAnimAllBak(ZoidState *zoid)
{
    if (zoid != 0) {
        zdLinearAnimAllBak1(zoid->joint->child, zoid->pose->child);
    }
}
