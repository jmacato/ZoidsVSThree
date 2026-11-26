#include "zoid3.h"

extern f32 atan2f(f32 y, f32 x);
extern void angLimit(f32 *angle);

f32 zdCoGrdRot(ZoidState *zoid, HSD_JObj **joint, f32 *direction, s32 scale)
{
    f32 x;
    f32 position[3];
    f32 delta[3];
    f32 angle;
    f32 next[3];
    s32 i;
    f32 turn;
    f32 angle2;
    f32 z;

    if (joint == 0)
        return 0.0f;
    if (*joint == 0)
        return 0.0f;
    for (i = 0; i < 3; i++) {
        position[i] = zoid->joint->child->matrix[i][3];
        delta[i] = (*joint)->matrix[i][3] - position[i];
        next[i] = (f32)scale * direction[i] + delta[i];
    }
    if (0.0f == delta[0] && 0.0f == delta[2])
        return 0.0f;
    if (delta[0] == next[0] && delta[2] == next[2])
        return 0.0f;
    z = delta[2];
    x = delta[0];
    angle = atan2f(x, z);
    z = next[2];
    angle2 = atan2f(next[0], z);
    angle = angle;
    angle2 = angle2;
    turn = angle2 - angle;
    turn = turn / 60.0;
    angLimit(&turn);
    return turn;
}
