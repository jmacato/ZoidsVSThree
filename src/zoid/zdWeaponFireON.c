#include "zoid3.h"

extern void zdWeaponChg(ZoidState *zoid);
extern void zdWeaponFireON_(ZoidState *zoid, s32 mount);

void zdWeaponFireON(ZoidState *zoid)
{
    WeaponMount *mount;
    ZoidControlData *control;
    s32 state;
    s32 index;
    s32 control_state;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        control = (ZoidControlData *)zoid->anim_data;
        if (zoid->weapon_mount == -1) {
            zdWeaponChg(zoid);
            return;
        }
        if (zoid->weapon_mount != -1 && zoid->selected_weapon_mount != -1 &&
            zoid->selected_weapon_mount == zoid->weapon_mount) {
            if (zoid->selected_weapon_mount != WEAPON_MOUNT_SUPER_ATTACK) {
                if (zoid->action < 13 || zoid->action > 22) {
                    mount = &zoid->weapon_mounts[zoid->selected_weapon_mount];
                    if (zoid->selected_weapon_mount == WEAPON_MOUNT_SUPER_ATTACK) {
                        mount->active = 1;
                    }
                    if (zoid->selected_weapon_mount != WEAPON_MOUNT_SUPER_ATTACK && mount->active != 0) {
                        control_state = control->field_0140[zoid->selected_weapon_mount];
                        if (control_state == 3 || control_state == 4) {
                            if (zoid->jump_phase != 0) {
                                return;
                            }
                            if (zoid->action == 26) {
                                return;
                            }
                            if (zoid->action == 25) {
                                return;
                            }
                            if (zoid->action == 23) {
                                return;
                            }
                            if (zoid->action == 24) {
                                return;
                            }
                        }
                        state = mount->state;
                        if (state == 2 || state == 3 || state == 4 || state == 5) {
                            if (state != 3) {
                                mount->state = 3;
                            }
                            if (zoid->selected_weapon_mount == WEAPON_MOUNT_SUPER_ATTACK &&
                                zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
                                for (index = 0; index < 10; index++) {
                                    zdWeaponFireON_(zoid, index);
                                }
                            } else {
                                zdWeaponFireON_(zoid, zoid->selected_weapon_mount);
                            }
                        }
                    }
                }
            }
        }
    }
}
