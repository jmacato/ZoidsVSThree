#include "zoid3.h"

extern void stCopyMatReset(HSD_JObj *joint, JointPose *pose);

void ZoidCopyMatReset(ZoidState *zoid)
{
    stCopyMatReset(zoid->joint, zoid->pose);
}
