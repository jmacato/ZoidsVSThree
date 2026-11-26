#include "zoid3.h"

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern void ZoidWalkSusumu(ZoidState *zoid);

void ZoidDash1(ZoidState *zoid)
{
    switch (zoid->action_phase) {
    case 0:
        ZoidSetAnim(zoid, 8);
        zoid->action_phase = 1;
        break;
    default:
        if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
            zoid->action = 0;
            zoid->requested_action = 0;
            ZoidSetAnim(zoid, 1);
            HSD_JObjAnimAll(zoid->joint);
        } else {
            zoid->action_phase++;
            ZoidWalkSusumu(zoid);
            if (zoid->action_phase < 30) {
                zoid->field_1C90[0] *= 1.1;
                zoid->field_1C90[0] += 0.01;
                zoid->field_1C90[2] *= 1.1;
                zoid->field_1C90[2] += 0.01;
            } else {
                zoid->field_1C90[0] *= 1.7;
                zoid->field_1C90[2] *= 1.7;
            }
        }
        break;
    }
}
