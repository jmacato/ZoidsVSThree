#include "zoid3.h"

void ik3dAnim(ZoidState *zoid, FootJoint *foot)
{
    register HSD_JObj *joint;
    register s32 n;

    if (zoid == (ZoidState *)0)
        return;
    if (foot == (FootJoint *)0)
        return;
    n = 0;
    joint = foot->joint;
    if (joint == (HSD_JObj *)0)
        return;
    foot->height = joint->matrix[1][3];
}
