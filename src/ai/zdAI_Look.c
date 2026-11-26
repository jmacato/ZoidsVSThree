#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

s32 zdAI_Look(s32 index)
{
    ZoidState *zoid;
    ZoidState *target;
    s32 slot;
    f32 angle;

    aiCmdReport("aiCmd-lock \n");
    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return 0;
    }
    if (zoid->target_pending == 0) {
        return 0;
    }
    slot = zoid->target_slot;
    if (slot < 0) {
        return 0;
    }
    if (slot >= 16) {
        return 0;
    }
    target = &Zoid[slot];
    if (target->joint == (void *)0) {
        return 0;
    }
    if (zoid == target) {
        return 0;
    }
    if (zoid->field_1C54 > 1.0f) {
        zoid->field_1C54 = 0.0f;
        return 0;
    }
    if (zoid->field_1C90[0] > 1.0f) {
        zoid->field_1C90[0] -= 0.1;
        if (zoid->field_1C90[0] < 0.0f) {
            zoid->field_1C90[0] = 0.0f;
        }
        return 0;
    }
    angle = zoid->target_angles[slot];
    if (absf(angle) < 2.0 * (3.1415926 * 5) / 180.0) {
        return 1;
    }
    if (angle > 0.0f) {
        zoid->requested_action = 0xB;
    } else {
        zoid->requested_action = 0xA;
    }
    zoid->field_1C54 = 1.0f;
    return 0;
}
