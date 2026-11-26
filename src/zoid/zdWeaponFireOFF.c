#include "zoid3.h"

extern void zdWeaponFireOFF_(ZoidState *zoid, s32 mount);

void zdWeaponFireOFF(ZoidState *zoid)
{
    WeaponMount *mount;
    s32 state;
    s32 index;
    void *data;
    s32 value;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        data = zoid->anim_data;
        if (zoid->weapon_mount == -1) {
            return;
        }
        mount = &zoid->weapon_mounts[zoid->weapon_mount];
        if (zoid->selected_weapon_mount == WEAPON_MOUNT_SUPER_ATTACK) {
            return;
        }
        if (zoid->weapon_mount == WEAPON_MOUNT_SUPER_ATTACK) {
            return;
        }
        if (mount->active == 0) {
            return;
        }
        state = mount->state;
        if (state == 3) {
            value = *(s32 *)((u8 *)data + 0x140 + zoid->weapon_mount * 4);
            if (zoid->animation_frame == 2 && zoid->animation_looped == 0) {
                return;
            }
            mount->state = 6;
        }
        if (state == 5) {
            mount->state = 6;
        }
        if (zoid->weapon_mount == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
            for (index = 0; index < 10; index++) {
                zdWeaponFireOFF_(zoid, index);
            }
        } else {
            zdWeaponFireOFF_(zoid, zoid->weapon_mount);
        }
    }
}
