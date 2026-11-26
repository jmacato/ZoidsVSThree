#include "zoid3.h"

extern s32 sWeaponEndF(s32 weapon);
extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);
extern void sWeaponLoopON(s32 weapon);
extern s32 sWeaponStopF(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);

s32 zdWeaponWpON(ZoidState *zoid, WeaponMount *mount)
{
    WeaponMountEntry *entry;
    s32 count;
    s32 i;
    register s32 weapon;
    register s32 animation;
    register s32 next;
    s32 slot;
    WeaponSlot *weaponSlot;

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
        if (sWeaponEndF(weapon) != 0) {
            animation = sWeaponGetAnim(weapon);
            if (animation == 1) {
                sWeaponStopOFF(weapon);
                sWeaponLoopON(weapon);
                continue;
            }
            if (animation == 0) {
                next = 1;
            } else {
                next = 0;
            }
            if (animation == 2) {
                if (sWeaponStopF(weapon) == 0) {
                    continue;
                }
                next = 1;
            }
            sWeaponSetAnim(weapon, next);
        }
        count++;
    }
    return count;
}
