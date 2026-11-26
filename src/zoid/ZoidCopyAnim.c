#include "zoid3.h"

extern void ZoidCopyAnim1(HSD_JObj *joint, JointPose *pose);

void ZoidCopyAnim(ZoidState *zoid)
{
    ZoidCopyAnim1(zoid->joint, zoid->pose);
}
