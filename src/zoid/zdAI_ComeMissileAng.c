#include "zoid3.h"

extern void aiCmdReport(const char *msg);
extern f32 sMisZdAng(ZoidState *zoid, f32 *angle);

f32 zdAI_ComeMissileAng(s32 index, s32 *out)
{
    ZoidState *zoid;
    f32 angle;
    f32 result;

    aiCmdReport("aiCmd-comeMissileAng \n");
    result = -1.0f;
    if (out != 0) {
        *out = 0;
    }
    if (index < 0) {
        return result;
    }
    if (index >= 16) {
        return result;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return result;
    }
    result = sMisZdAng(zoid, &angle);
    if (out != 0) {
        *out = (s32)(180.0f * angle / 3.1415926);
    }
    return result;
}
