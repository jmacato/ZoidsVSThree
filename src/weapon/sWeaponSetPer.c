#include "zoid3.h"

extern void sWeaponSetPer00(s32 index, f32 opacity);

void sWeaponSetPer(ZoidState *zoid, f32 opacity)
{
    s32 slot;
    s32 index;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        for (slot = 0; slot < 30; slot++) {
            index = zoid->weapon_slots[slot].weapon;
            if (index != -1) {
                sWeaponSetPer00(index, opacity);
            }
        }
    }
}
