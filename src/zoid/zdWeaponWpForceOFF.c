#include "zoid3.h"

extern s32 sWeaponEndF(s32 weapon);
extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);
extern void sWeaponLoopON(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);

s32 zdWeaponWpForceOFF(ZoidState *zoid, WeaponMount *mount)
{
    s32 weapon;
    WeaponMountEntry *entry;
    s32 i;
    s32 slot;
    s32 animation;
    WeaponSlot *weaponSlot;
    s32 count;

    if (mount->active == 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 4; i++) {
        entry = &mount->entries[i];
        if (entry->active == 0) {
            continue;
        }
        slot = entry->slot;
        if (slot == -1) {
            entry->active = 0;
            continue;
        }
        weaponSlot = &zoid->weapon_slots[slot];
        weapon = weaponSlot->weapon;
        if (weapon == -1) {
            continue;
        }
        sWeaponStopOFF(weapon);
        animation = sWeaponGetAnim(weapon);
        if (animation == 4) {
            continue;
        }
        switch (animation) {
        case 0:
        case 1:
        case 2:
            sWeaponSetAnim(weapon, 4);
            break;
        case 3:
            sWeaponLoopON(weapon);
            if (sWeaponEndF(weapon) != 0) {
                sWeaponSetAnim(weapon, 4);
            }
            break;
        }
        count++;
    }
    return count;
}
