#include "zoid3.h"

extern void OSReport(const char *fmt, ...);
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);

void ZoidActWin(ZoidState *zoid)
{
    s32 changed;

    changed = 0;
    if (zoid->current_animation != 3) {
        changed = 1;
    }
    if (changed != 0) {
        if (zoid == Zoid) {
            OSReport("mot-Win\n");
        }
        ZoidSetAnim(zoid, 3);
    }
    zoid->field_1C34 = 0;
}
