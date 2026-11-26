#include "zoid3.h"

extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);
extern void sWeaponLoopOFF(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);

void zdWeaponForceFire1_(ZoidState *zoid, s32 selected)
{
    WeaponMount *mount = &zoid->weapon_mounts[selected];
    s32 index;
    s32 slot;

    if (mount->active != 0 && zoid->super_attack_input == 0) {
        for (index = 0; index < 4; index++) {
            if (mount->entries[index].active != 0) {
                slot = mount->entries[index].slot;
                if (slot != -1) {
                    if (zoid->death_started != 0) {
                        sWeaponLoopOFF(zoid->weapon_slots[slot].weapon);
                    } else {
                        if (sWeaponGetAnim(zoid->weapon_slots[slot].weapon) != 2) {
                            sWeaponSetAnim(zoid->weapon_slots[slot].weapon, 2);
                        }
                        sWeaponLoopOFF(zoid->weapon_slots[slot].weapon);
                        sWeaponStopOFF(zoid->weapon_slots[slot].weapon);
                    }
                }
            }
        }
    }
}
