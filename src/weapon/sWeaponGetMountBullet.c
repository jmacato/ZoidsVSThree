#include "zoid3.h"

extern s32 sWeaponGetBullet(s32 weapon);
extern void sWeaponSetCounter(s32 index);

s32 sWeaponGetMountBullet(ZoidState *zoid, s32 index)
{
    WeaponMount *mount;
    s32 total;
    s32 i;
    s32 found;
    s32 slot;
    s32 weapon;

    if (zoid == (void *)0) {
        return 0;
    }
    if (zoid->joint == (void *)0) {
        return 0;
    }
    if (index == -1) {
        return 0;
    }
    mount = &zoid->weapon_mounts[index];
    if (mount->active == 0) {
        return 0;
    }
    total = 0;
    found = 0;
    for (i = 0; i < 4; i++) {
        if (mount->entries[i].active != 0) {
            slot = mount->entries[i].slot;
            if (slot == -1) {
                mount->entries[i].active = 0;
            } else {
                weapon = zoid->weapon_slots[slot].weapon;
                if (weapon == -1) {
                    mount->entries[i].active = 0;
                    mount->entries[i].slot = -1;
                } else {
                    found++;
                    total += sWeaponGetBullet(weapon);
                    sWeaponSetCounter(weapon);
                }
            }
        }
    }
    if (found == 0) {
        mount->active = 0;
    }
    return total;
}
