#include "zoid3.h"
#define sColPt sColPtHdr
#include "ground_collision.h"
#undef sColPt
extern f32 sColPt(Vec3 *start, Vec3 *end, GroundMask mask);

extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern void angLimit(f32 *angle);
extern f32 sColPtAll(Vec3 *start, Vec3 *end, GroundMask mask);

s32 zdFaceAtk(ZoidState *zoid, f32 distance, f32 offset)
{
    Vec3 origin;
    Vec3 target;
    Vec3 start;
    f32 angle;
    HSD_JObj *joint;
    s32 i;
    f32 res;
    f32 two = 2.0f;
    f32 sine_angle;
    f32 t1;
    f32 t2;
    f32 t3;

    joint = 0;
    if (joint == 0) {
        joint = *(HSD_JObj **)zoid->head_coobj;
    }
    if (joint == 0) {
        joint = *(HSD_JObj **)zoid->neck_coobj;
    }
    if (joint == 0) {
        joint = *(HSD_JObj **)zoid->bust_coobj;
    }
    if (joint == 0) {
        joint = *(HSD_JObj **)zoid->hip_coobj;
    }
    if (joint == 0) {
        joint = (HSD_JObj *)zoid->camera_joint;
    }
    if (joint == 0) {
        joint = zoid->joint->child;
    }
    if (joint == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        ((f32 *)&origin)[i] = joint->matrix[i][3];
        ((f32 *)&target)[i] = ((f32 *)&origin)[i];
        ((f32 *)&start)[i] = ((f32 *)&origin)[i];
    }
    angle = zoid->heading + offset;
    angLimit(&angle);
    sine_angle = angle;
    target.x += distance * sinf(sine_angle);
    t1 = angle;
    target.z += distance * cosf(t1);
    t2 = angle;
    start.x -= two * sinf(t2);
    t3 = angle;
    start.z -= two * cosf(t3);
    target.y += distance / 2.0f;
    res = sColPtAll(&start, &target, (GroundMask){{31, 0, 0, 0}});
    if (res != GROUND_NO_HIT) {
        return 1;
    }
    res = sColPt(&target, &start, (GroundMask){{31, 0, 0, 0}});
    if (res != GROUND_NO_HIT) {
        return 1;
    }
    return 0;
}
