#include "zoid3.h"

extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern void zdAnimRate(ZoidState *zoid, f32 rate);

void ZoidActDeadly(ZoidState *zoid)
{
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        switch (zoid->action_phase) {
        case 0:
            ZoidSetAnim(zoid, 0x34);
            zoid->action_phase = 1;
            break;
        case 1:
            if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
                ZoidSetAnim(zoid, 0x38);
                zoid->action_phase = 2;
            } else {
                break;
            }
        case 2:
            if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
                ZoidSetAnim(zoid, 0x38);
                zoid->action_phase = 3;
            } else {
                break;
            }
        case 3:
            if (zoid->animation_stopped != 0 || zoid->animation_looped != 0) {
                ZoidSetAnim(zoid, 0x38);
                zoid->action_phase = 4;
            } else {
                break;
            }
        case 4:
            zdAnimRate(zoid, 0.0f);
            zoid->death_pending = 1;
            break;
        }
    }
}
