#include "zoid3.h"

extern u8 sWeapon[];
extern void sWeaponSearchSightClear(void *state);

void zdWeaponSightClear(ZoidState *zoid, s32 selected)
{
    WeaponMount *mount;
    WeaponMountEntry *entry;
    WeaponSlot *weapon_slot;
    s32 index;
    s32 slot;
    s32 weapon;

    if (zoid != 0 && zoid->joint != 0 && selected != -1) {
        mount = &zoid->weapon_mounts[selected];
        if (mount->active != 0) {
            for (index = 0; index < 4; index++) {
                entry = &mount->entries[index];
                if (entry->active != 0) {
                    slot = entry->slot;
                    if (slot != -1) {
                        weapon_slot = &zoid->weapon_slots[slot];
                        weapon = weapon_slot->weapon;
                        sWeaponSearchSightClear(&sWeapon[weapon * 0x6DC]);
                    }
                }
            }
        }
    }
}
