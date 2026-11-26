#include "zoid3.h"

extern void aiCmdReport(const char *msg);
extern f32 atan2f(f32 y, f32 x);

s32 zdAI_angPoint(s32 index, f32 x, f32 z)
{
    ZoidState *zoid;
    f32 angle;

    aiCmdReport("aiCmd-angPoint \n");
    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    if (x == zoid->position[0] && z == zoid->position[2]) {
        return 0;
    }
    x = x - zoid->position[0];
    z = z - zoid->position[2];
    angle = atan2f(x, z);
    angle = angle - zoid->heading;
    return (s32)(360.0 * (angle / (2.0 * 3.1415926)));
}
