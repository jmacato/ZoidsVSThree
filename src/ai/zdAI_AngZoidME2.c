#include "zoid3.h"

extern void aiCmdReport(const char *msg);

s32 zdAI_AngZoidME2(s32 index, s32 target)
{
    ZoidState *zoid;
    ZoidState *other;
    f32 degrees;
    s32 result;

    aiCmdReport("aiCmd-angZoidME2 \n");
    if (index < 0) {
        return -1;
    }
    if (index >= 16) {
        return -1;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return -1;
    }
    if (target < 0) {
        return -1;
    }
    if (target >= 16) {
        return -1;
    }
    other = &Zoid[target];
    if (other->joint == (void *)0) {
        return -1;
    }
    degrees = 180.0 * zoid->target_angles[target] / 3.1415926;
    result = (s32)degrees;
    return result;
}
