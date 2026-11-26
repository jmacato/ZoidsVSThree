#include "zoid3.h"

extern void stSetFlag(HSD_JObj *joint, JointPose *pose, f32 alpha);
extern void sWeaponSetPer(ZoidState *zoid, f32 alpha);

void zdTrans1(ZoidState *zoid)
{
    stSetFlag(zoid->joint, zoid->pose, zoid->transformation);
    sWeaponSetPer(zoid, zoid->transformation);
    if (zoid->transformation == 1.0)
        zoid->transparency_flags &= ~1;
    else
        zoid->transparency_flags |= 1;
}
