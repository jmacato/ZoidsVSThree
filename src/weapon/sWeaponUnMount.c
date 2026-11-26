#include "zoid3.h"

extern void sWeaponPurge(s32 index);

void sWeaponUnMount(ZoidState *zoid, s32 slot)
{
    s32 weapon;

    if (zoid != (void *)0 && zoid->joint != (void *)0 && slot >= 0 && slot < 30) {
        weapon = zoid->weapon_slots[slot].weapon;
        sWeaponPurge(weapon);
    }
}
