#include "zoid3.h"

extern void OSReport(const char *fmt, ...);
extern s32 sWeaponSetU(s32 weapon, ZoidState *zoid, s32 slot, WeaponMount *mount, s32 flag);

void sWeaponMountU(s32 weapon, ZoidState *zoid, s32 slot, s32 mount, s32 flag)
{
    WeaponMount *entry;
    s32 result;

    OSReport("mount wp    zoid=%d mt=%d act=%d wp=%d\n", zoid != 0 ? zoid->type : -1, slot, mount, weapon);
    if (zoid != (void *)0 && zoid->joint != (void *)0 && weapon > 0 && mount >= 0) {
        entry = &zoid->weapon_mounts[mount];
        result = sWeaponSetU(weapon, zoid, slot, entry, flag);
        if (result != -1) {
            zoid->mount_has_weapon[mount] = 1;
        }
    }
}
