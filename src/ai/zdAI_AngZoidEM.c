#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

s32 zdAI_AngZoidEM(s32 index)
{
    ZoidState *zoid;
    ZoidState *target;
    s32 target_index;
    f32 degrees;
    s32 result;

    aiCmdReport("aiCmd-angZoidEM \n");
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
    target_index = zoid->target_slot;
    if (target_index < 0) {
        return -1;
    }
    if (target_index >= 16) {
        return -1;
    }
    target = &Zoid[target_index];
    if (target->joint == (void *)0) {
        return -1;
    }
    degrees = 180.0 * target->target_angles[index] / 3.1415926;
    result = (s32)degrees;
    return result;
}
