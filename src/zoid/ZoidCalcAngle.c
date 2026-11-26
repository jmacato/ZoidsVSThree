#include "zoid3.h"

extern f32 atan2f(f32 y, f32 x);
extern void angLimit(f32 *angle);

f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point)
{
    f32 dx;
    f32 dy;
    f32 dz;
    f32 theta;
    f32 angle;

    if (zoid == (void *)0) {
        return 100.0f;
    }
    if (zoid->joint == (void *)0) {
        return 100.0f;
    }
    dx = point->x - zoid->position[0];
    dy = point->y - zoid->position[1];
    dz = point->z - zoid->position[2];
    if (dx == 0.0f && dz == 0.0f) {
        return 100.0f;
    }
    theta = atan2f(dx, dz);
    angle = theta - zoid->heading;
    angLimit(&angle);
    return angle;
}
