#include "zoid3.h"
#include "ground_collision.h"

extern void angLimit(f32 *angle);
extern f32 sColRealPt(Vec3 *a, Vec3 *b, GroundMask *c);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);

f32 zdFreeLen(ZoidState *zoid, f32 length, f32 offset)
{
    Vec3 b;
    Vec3 a;
    f32 ang;
    GroundMask copy;
    HSD_JObj *joint;
    f32 sine_angle;
    f32 angle;
    s32 i;
    f32 r;

    joint = *(HSD_JObj **)zoid->bust_coobj;
    if (joint == 0) {
        joint = *(HSD_JObj **)zoid->hip_coobj;
    }
    if (joint == 0) {
        joint = *(HSD_JObj **)zoid->neck_coobj;
    }
    if (joint == 0) {
        joint = (HSD_JObj *)zoid->camera_joint;
    }
    if (joint == 0) {
        return 0.0f;
    }
    for (i = 0; i < 3; i++) {
        (&b.x)[i] = joint->matrix[i][3];
        (&a.x)[i] = joint->matrix[i][3];
    }
    ang = zoid->heading + offset;
    angLimit(&ang);
    sine_angle = ang;
    a.x = a.x + length * sinf(sine_angle);
    angle = ang;
    a.z = a.z + length * cosf(angle);
    {
        GroundMask mask = {{0x1F, 0, 0, 0}};
        copy = mask;
        r = sColRealPt(&b, &a, &copy);
    }
    if (r == 10000.0f) {
        r = 1.01f;
    }
    return r * length;
}
