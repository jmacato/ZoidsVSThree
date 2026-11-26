#include "zoid3.h"

extern s32 zdWp1Slider(ZoidState *zoid, s32 index, s32 flag);

s32 zdWpSlider(ZoidState *zoid, s32 slot)
{
    s32 i;
    s32 target;
    s32 changed;

    if (zoid == 0) {
        return 0;
    }
    if (zoid->joint == 0) {
        return 0;
    }
    target = slot + 1;
    if (slot == -1) {
        target = -1;
    }
    if (slot == 0x13) {
        target = 0;
    }
    changed = 0;
    for (i = 0; i < 11; i++) {
        if (i != target) {
            if (zdWp1Slider(zoid, i, 0) != 0) {
                changed = 1;
            }
        }
    }
    if (changed != 0) {
        return 1;
    }
    if (target == -1) {
        return 0;
    }
    if (zdWp1Slider(zoid, target, 1) != 0) {
        return 1;
    }
    return 0;
}
