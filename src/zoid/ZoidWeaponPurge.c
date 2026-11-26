#include "zoid3.h"

extern void sWeaponPurge(s32 weapon);

void ZoidWeaponPurge(ZoidState *zoid)
{
    s32 i;
    s32 weapon;
    for (i = 0; i < 30; i++) {
        weapon = zoid->weapon_slots[i].weapon;
        if (weapon != -1)
            sWeaponPurge(weapon);
    }
}
