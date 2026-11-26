#include "zoid3.h"

extern s32 zdWeaponChg0(ZoidState *zoid);

void zdWeaponChgSlot(ZoidState *zoid, s32 slot)
{
    s32 i;

    if (zoid != (void *)0 && zoid->joint != (void *)0 && zoid->death_started == 0) {
        zoid->weapon_mount_count = zdWeaponChg0(zoid);
        if (zoid->weapon_mount_count >= 1 && zoid->weapon_mount_count > 0) {
            zoid->selected_weapon_mount = slot;
            if (slot != -1) {
                for (i = 0; i < 10; i++) {
                    if (zoid->selected_weapon_mount > 9) {
                        zoid->selected_weapon_mount = 0;
                    }
                    if (*(s32 *)&zoid->weapon_mounts[zoid->selected_weapon_mount] != 0) {
                        break;
                    }
                    zoid->selected_weapon_mount = zoid->selected_weapon_mount + 1;
                }
            }
        }
    }
}
