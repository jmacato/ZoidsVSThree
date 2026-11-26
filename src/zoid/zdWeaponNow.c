#include "zoid3.h"

s32 zdWeaponNow(ZoidState *zoid)
{
    s32 count;
    s32 i;
    s32 j;
    WeaponMount *mount;
    WeaponMountEntry *entry;

    if (zoid == (void *)0)
        return 0;
    if (zoid->joint == (void *)0)
        return 0;
    if (zoid->death_started != 0)
        return 0;
    if (zoid->selected_weapon_mount == WEAPON_MOUNT_SUPER_ATTACK)
        return 0;
    if (zoid->selected_weapon_mount == -1)
        return 0;
    if (zoid->selected_weapon_mount > 9)
        zoid->selected_weapon_mount = 0;
    count = 0;
    for (i = 0; i < 10; i++) {
        mount = &zoid->weapon_mounts[i];
        if (mount->active == 0)
            continue;
        for (j = 0; j < 4; j++) {
            entry = &mount->entries[j];
            if (entry->active != 0) {
                if (entry->slot != -1)
                    break;
                entry->active = 0;
            }
        }
        if (j == 4)
            mount->active = 0;
        else
            count++;
    }
    zoid->weapon_mount_count = count;
    if (count == 0)
        return 1;
    if (zoid->weapon_mounts[zoid->selected_weapon_mount].active != 0)
        return 1;
    zoid->selected_weapon_mount++;
    if (zoid->selected_weapon_mount > 9)
        zoid->selected_weapon_mount = 0;
    return 0;
}
