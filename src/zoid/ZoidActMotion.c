#include "zoid3.h"

extern void ZoidSetAnim(ZoidState *zoid, s32 anim);

void ZoidActMotion(ZoidState *zoid)
{
    s32 changed;

    changed = 0;
    if (zoid->current_animation != zoid->field_1DEC) {
        changed = 1;
    }
    if (zoid->animation_looped != 0) {
        changed = 1;
    }
    if (zoid->animation_stopped != 0) {
        changed = 1;
    }
    if (changed != 0) {
        ZoidSetAnim(zoid, zoid->field_1DEC);
    }
}
