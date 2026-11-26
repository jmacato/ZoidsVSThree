#include "zoid3.h"

typedef struct WeaponMountEntryV3 {
    s32 active;
    s32 slot;
    s32 reserved_08;
} WeaponMountEntryV3;

typedef struct WeaponMountV3 {
    s32 active;
    s32 reserved_04;
    WeaponMountEntryV3 entries[4];
} WeaponMountV3;

typedef struct WeaponV3 {
    u8 reserved_000[0x3FC];
    s32 bullet_kind;
    u8 reserved_400[0x6DC - 0x400];
} WeaponV3;

extern WeaponV3 sWeapon[];
extern void sWeaponSearchSight(WeaponV3 *weapon);

void zdSearchSight(ZoidState *zoid, s32 index)
{
    s32 slot;
    s32 weapon;
    WeaponSlot *weapon_slot;
    WeaponMountV3 *mount;
    s32 i;
    WeaponMountEntryV3 *entry;
    WeaponV3 *state;

    if (zoid != (void *)0 && zoid->joint != (void *)0 && index != -1) {
        mount = (WeaponMountV3 *)&zoid->weapon_mounts[index];
        if (mount->active != 0) {
            for (i = 0; i < 4; i++) {
                entry = &mount->entries[i];
                if (entry->active != 0) {
                    slot = entry->slot;
                    if (slot != -1) {
                        weapon_slot = &zoid->weapon_slots[slot];
                        weapon = weapon_slot->weapon;
                        if (weapon != -1) {
                            state = &sWeapon[weapon];
                            if (state->bullet_kind == 1) {
                                sWeaponSearchSight(state);
                            }
                        }
                    }
                }
            }
        }
    }
}
