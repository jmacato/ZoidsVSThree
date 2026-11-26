#include "zoid3.h"

extern s32 bitTBL[16];

s32 chkBossArea(ZoidState *zoid)
{
    s32 i;
    ZoidState *other;
    void *anim;
    s32 bits;
    union {
        f32 f;
        u32 u;
    } angle;

    bits = zoid->contact_bits;
    if (bits == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        if ((bits & bitTBL[i]) == 0) {
            continue;
        }
        other = &Zoid[i];
        if (other->joint == 0) {
            continue;
        }
        anim = other->anim_data;
        if (anim == 0) {
            continue;
        }
        if (*(s32 *)((u8 *)anim + 0x100) == 0) {
            continue;
        }
        angle.f = zoid->target_angles[i];
        angle.u &= 0x7FFFFFFF;
        if (angle.f > 3.1415926 / 2.0) {
            continue;
        }
        return 1;
    }
    return 0;
}
