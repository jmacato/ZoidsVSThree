#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void angLimit(f32 *angle);
extern void zdChgNormal(ZoidState *zoid);
extern void zdFreeAng(ZoidState *zoid, f32 angle);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

s32 zdAI_freeAng(s32 index, s32 angle)
{
    ZoidState *zoid;
    ZoidAIState *ai;
    f32 base;
    f32 turn;
    s32 action;

    aiCmdReport("aiCmd-freeAng \n");
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
    if (zoid->field_1360 != 0) {
        return 0;
    }
    ai = zoid->ai;
    if (ai == 0) {
        return 1;
    }
    ai->mode = 999;
    action = zoid->action;
    if (zoid->field_2060 == -1) {
        base = zoid->field_205C;
        turn = base - zoid->heading;
        angLimit(&turn);
        if (action >= 3 && action <= 11) {
            zoid->field_1C54 = 1.0f;
            if (absf(turn) < 2.0 * (3.1415926 * 5) / 180.0) {
                zoid->field_1C54 = 0.0f;
                zoid->heading = zoid->field_205C;
                zdChgNormal(zoid);
                return 1;
            }
            return 0;
        }
        if (turn == 0.0f) {
            return 1;
        }
        if (absf(turn) < 2.0 * (3.1415926 * 5) / 180.0) {
            zoid->field_1C54 = 0.0f;
            zoid->heading = base;
            zdChgNormal(zoid);
            return 1;
        }
        if (turn > 0.0f) {
            zoid->requested_action = 5;
        } else {
            zoid->requested_action = 4;
        }
        if (action == 0) {
            zoid->action = zoid->requested_action;
            zoid->action_phase = 0;
        }
        zoid->field_1C54 = 1.0f;
        return 0;
    }
    zoid->field_1C90[0] = 0.0f;
    zdFreeAng(zoid, (f32)angle);
    return 0;
}
