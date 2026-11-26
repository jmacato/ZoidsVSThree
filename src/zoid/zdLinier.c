#include "zoid3.h"

extern void zdSetXYZ(ZoidState *zoid);
extern void ZoidLinerAnimNextXor(HSD_JObj *joint, JointPose *pose, f32 fraction, ZoidState *zoid);

void zdLinier(ZoidState *zoid)
{
    zdSetXYZ(zoid);
    if (zoid->interpolation_remaining != 0 && zoid->interpolation_duration != 0) {
        f32 fraction = ((f32)zoid->interpolation_duration - (f32)zoid->interpolation_remaining)
                       / (f32)zoid->interpolation_duration;

        ZoidLinerAnimNextXor(zoid->joint->child->child, zoid->pose->child->child, fraction, zoid);
        zoid->interpolation_remaining--;
    }
    if (zoid->interpolation_remaining < 0) {
        zoid->interpolation_remaining = 0;
    }
    if (zoid->interpolation_duration < 0) {
        zoid->interpolation_duration = 0;
    }
}
