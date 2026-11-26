#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

s32 zdAI_cmpHigh(s32 index)
{
    ZoidState *zoid;
    ZoidState *other;
    ZoidAIState *ai;
    s32 target;
    f32 dy;

    aiCmdReport("aiCmd-cmpHigh \n");
    if (index < 0) {
        return 1;
    }
    if (index >= 16) {
        return 1;
    }
    zoid = &Zoid[index];
    if (zoid->joint == 0) {
        return 1;
    }
    ai = zoid->ai;
    if (ai == 0) {
        return 1;
    }
    other = 0;
    target = ai->target_index;
    if (target >= 0 && target < 16) {
        other = &Zoid[target];
    }
    if (other != 0 && other->slot == zoid->slot) {
        other = 0;
    }
    if (other != 0 && other->joint == 0) {
        other = 0;
    }
    if (other == 0) {
        target = zoid->target_slot;
        if (target >= 0 && target < 16) {
            other = &Zoid[target];
        }
        if (other != 0 && other->slot == zoid->slot) {
            other = 0;
        }
        if (other != 0 && other->joint == 0) {
            other = 0;
        }
    }
    if (other == 0) {
        return 1;
    }
    dy = absf(zoid->position[1] - other->position[1]);
    if (dy < 10.0f) {
        return 1;
    }
    return 0;
}
