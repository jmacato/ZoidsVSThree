#include "zoid3.h"

s32 zdWeaponChg0(ZoidState *zoid)
{
    WeaponMountEntry *entry;
    s32 j;
    WeaponMount *mount;
    s32 i;
    s32 count;

    if (zoid == (void *)0) {
        return 0;
    }
    if (zoid->joint == (void *)0) {
        return 0;
    }
    if (zoid->death_started != 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 10; i++) {
        mount = &zoid->weapon_mounts[i];
        if (mount->active != 0) {
            for (j = 0; j < 4; j++) {
                entry = &mount->entries[j];
                if (entry->active != 0) {
                    if (entry->slot == -1) {
                        entry->active = 0;
                    } else {
                        break;
                    }
                }
            }
            if (j == 4) {
                mount->active = 0;
            } else {
                count++;
            }
        }
    }
    zoid->weapon_mount_count = count;
    return count;
}
