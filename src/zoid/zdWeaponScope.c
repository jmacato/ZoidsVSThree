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
    u8 reserved_000[0x38];
    u32 field_038;
    u8 reserved_03C[0x6DC - 0x3C];
} WeaponV3;

extern WeaponV3 sWeapon[];

s32 zdWeaponScope(ZoidState *zoid, s32 index)
{
    WeaponMountV3 *mount;
    s32 i;
    s32 slot;
    s32 weapon;
    WeaponMountEntryV3 *entry;
    WeaponV3 *state;
    WeaponSlot *weapon_slot;

    if (zoid == 0) {
        return 0;
    }
    if (zoid->joint == 0) {
        return 0;
    }
    if (index == -1) {
        return 0;
    }
    mount = (WeaponMountV3 *)&zoid->weapon_mounts[index];
    if (mount->active == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        entry = &mount->entries[i];
        if (entry->active == 0) {
            continue;
        }
        slot = entry->slot;
        if (slot == -1) {
            continue;
        }
        weapon_slot = &zoid->weapon_slots[slot];
        weapon = weapon_slot->weapon;
        if (weapon == -1) {
            continue;
        }
        state = &sWeapon[weapon];
        if (state->field_038 != 0) {
            return state->field_038;
        }
    }
    return 0;
}
