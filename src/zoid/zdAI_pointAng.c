#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void angLimit(f32 *angle);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);

void zdAI_pointAng(s32 index, s32 a, s32 b, s32 *out_x, s32 *out_z)
{
    ZoidState *zoid;
    f32 pos[3];
    f32 angle;
    s32 i;
    f32 sine_angle;
    f32 cosine_angle;

    aiCmdReport("aiCmd-pointAng \n");
    if (out_x == 0 || out_z == 0)
        return;
    if (index < 0)
        return;
    if (index >= 16)
        return;
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0)
        return;
    for (i = 0; i < 3; i++) {
        pos[i] = zoid->position[i];
    }
    angle = zoid->heading + 2.0 * (3.1415926 * (f32)a) / 360.0;
    angLimit(&angle);
    sine_angle = angle;
    pos[0] += (f32)b * sinf(sine_angle);
    cosine_angle = angle;
    pos[2] += (f32)b * cosf(cosine_angle);
    *out_x = (s32)pos[0];
    *out_z = (s32)pos[2];
}
