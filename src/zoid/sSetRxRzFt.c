#pragma readonly_strings on
#include "zoid3.h"

extern void __assert(const char *file, s32 line, const char *message);
extern f32 atan2f(f32 y, f32 x);

#pragma auto_inline off
static inline f32 HSD_JObjGetTranslationX(HSD_JObj *joint)
{
    joint ? (void)0 : __assert("jobj.h", 1009, "jobj");
    return joint->translation.x;
}
static inline f32 HSD_JObjGetTranslationZ(HSD_JObj *joint)
{
    joint ? (void)0 : __assert("jobj.h", 1033, "jobj");
    return joint->translation.z;
}

void sSetRxRzFt(ZoidState *zoid, FootJoint *front, FootJoint *back, f32 *rx, f32 *rz)
{
    f32 dx;
    f32 y;
    f32 mx;
    f32 dy;
    f32 mz;
    f32 angle_x;
    f32 angle_z;
    f32 ay;

    if (front->joint == (void *)0) {
        return;
    }
    if (back->joint == (void *)0) {
        return;
    }
    y = (front->ground + back->ground) / 2.0f;
    mx = (HSD_JObjGetTranslationX(front->joint) + HSD_JObjGetTranslationX(back->joint)) / 2.0f;
    mz = (HSD_JObjGetTranslationZ(front->joint) + HSD_JObjGetTranslationZ(back->joint)) / 2.0f;
    ay = zoid->position[1] - y;
    angle_x = atan2f(ay, mz);
    *rx = *rx + (angle_x - *rx) * 0.25;
    dy = front->ground - back->ground;
    dx = HSD_JObjGetTranslationX(front->joint) - HSD_JObjGetTranslationX(back->joint);
    angle_z = atan2f(dy, dx);
    *rz = *rz + (angle_z - *rz) * 0.25;
}
