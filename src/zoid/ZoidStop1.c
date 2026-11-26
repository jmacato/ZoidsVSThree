#include "zoid3.h"
#include "angle.h"

extern void ZoidSisei(ZoidState *zoid);
extern void ssSmoke(ZoidState *zoid);
extern void zdVoiceSc(ZoidState *zoid, s32 id);
extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void zdLinierTm(ZoidState *zoid, s32 frames);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern void zdStop1Susumu(ZoidState *zoid);
extern void rotAngStopA(ZoidState *zoid, f32 angle);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

void ZoidStop1(ZoidState *zoid)
{
    u8 *data;
    u8 *ai;

    data = zoid->anim_data;
    if (data == 0)
        return;
    ai = (u8 *)zoid->ai;
    if (ai == 0)
        return;
    ZoidSisei(zoid);
    ssSmoke(zoid);
    zoid->field_1C04 |= 1;
    switch (zoid->action_phase) {
    case 0:
        if (zoid->target_pending != 0) {
            zdVoiceSc(zoid, 0x1d);
        }
        ZoidSetAnim(zoid, 9);
        zdLinierTm(zoid, 0x1e);
        zoid->action_phase = 1;
        zoid->field_1D5C = zoid->heading;
        zoid->field_1D60 = zoid->field_1C90[2];
        break;
    default:
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0 || 0.0f == zoid->field_1D60) {
            zoid->action = 0;
            zoid->requested_action = 0;
            ZoidSetAnim(zoid, 1);
            HSD_JObjAnimAll(zoid->joint);
            zoid->field_1D60 = 0.0f;
            zoid->field_1C90[2] = 0.0f;
            zoid->field_1C90[0] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
            zoid->step_heading = zoid->heading;
            break;
        }
        switch (zoid->requested_action) {
        case 2:
        case 13:
        case 23:
        case 24:
        case 25:
        case 26:
        case 45:
        case 46:
        case 47:
        case 48:
            zoid->action = 0;
            zoid->field_1C90[2] = zoid->field_1D60;
            zoid->field_1C90[0] = zoid->field_1D60;
            zoid->field_1C90[1] = zoid->field_1D60;
        }
        zoid->action_phase++;
        zoid->field_1BFC = 0;
        zdStop1Susumu(zoid);
        if (zoid->action_phase < 30) {
            zoid->field_1D60 -= 2.0 * ((f32) * (s32 *)(data + 0x310) / 10000.0);
            zoid->field_1C90[0] -= 2.0 * ((f32) * (s32 *)(data + 0x310) / 10000.0);
            zoid->field_1C90[1] -= 2.0 * ((f32) * (s32 *)(data + 0x310) / 10000.0);
            zoid->field_1C90[2] -= 2.0 * ((f32) * (s32 *)(data + 0x310) / 10000.0);
        } else {
            zoid->field_1D60 -= 3.0 * ((f32) * (s32 *)(data + 0x310) / 10000.0);
            zoid->field_1C90[0] -= 3.0 * ((f32) * (s32 *)(data + 0x310) / 10000.0);
            zoid->field_1C90[1] -= 3.0 * ((f32) * (s32 *)(data + 0x310) / 10000.0);
            zoid->field_1C90[2] -= 3.0 * ((f32) * (s32 *)(data + 0x310) / 10000.0);
        }
        if (zoid->action_phase > 57) {
            zoid->field_1D60 = 0.0f;
            zoid->field_1C90[2] = 0.0f;
            zoid->field_1C90[0] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
        }
        if (!(zoid->ai != 0 && zoid->ai_active != 0 && *(s32 *)((u8 *)zoid->ai + 0x40) != 0)) {
            if (absf(zoid->field_1C54) < 0.2) {
                zoid->field_1D60 = 0.0f;
            }
        }
        if (zoid->field_1D60 < 0.0f) {
            zoid->field_1D60 = 0.0f;
        }
        if (zoid->field_1C90[0] < 0.0f) {
            zoid->field_1C90[0] = 0.0f;
        }
        if (zoid->field_1C90[2] < 0.0f) {
            zoid->field_1C90[2] = 0.0f;
        }
        if (zoid->field_1C90[1] < 0.0f) {
            zoid->field_1C90[1] = 0.0f;
        }
        if (zoid->target_pending != 0 || zoid->lock_active != 0) {
            rotAngStopA(zoid, zoid->field_1E94);
        } else if (zoid->ai_active == 0) {
            if (zoid->field_1C74 < -0.1) {
                rotAngStopA(zoid, DEG2RAD_D(10) + zoid->heading);
            }
            if (zoid->field_1C74 > 0.1) {
                rotAngStopA(zoid, zoid->heading - DEG2RAD_D(10));
            }
        }
    }
}
