#include "zoid3.h"

extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);
extern f32 zdColPosY(f32 *point, s32 flags);

f32 zdGoY(ZoidState *zoid, f32 angle, f32 distance)
{
    f32 origin[3];
    f32 target[3];
    s32 axis;
    f32 a0;
    f32 a1;

    if (zoid == (void *)0) {
        return 0.0f;
    }
    if (zoid->joint == (void *)0) {
        return 0.0f;
    }
    for (axis = 0; axis < 3; axis++) {
        origin[axis] = zoid->position[axis];
        target[axis] = zoid->position[axis];
    }
    origin[1] = zoid->ground_height;
    target[1] = zoid->ground_height;
    a0 = angle + zoid->heading;
    target[0] += distance * sinf(a0);
    a1 = angle + zoid->heading;
    target[2] += distance * cosf(a1);
    target[1] = zdColPosY(target, 0);
    return target[1] - origin[1];
}
