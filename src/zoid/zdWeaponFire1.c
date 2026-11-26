#include "zoid3.h"

extern void zdWeaponFire1_(ZoidState *zoid, s32 mount);
extern void zdWeaponFireVoice(ZoidState *zoid);

void zdWeaponFire1(ZoidState *zoid)
{
    WeaponMount *mount;
    s32 input;
    ZoidControlData *control;
    s32 state;
    s32 index;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        control = (ZoidControlData *)zoid->anim_data;
        if (control->field_0100 == 0) {
            if (zoid->field_1DA0 != -1)
                return;
        }
        if (zoid->weapon_mount == -1)
            return;
        if (zoid->selected_weapon_mount == -1)
            return;
        if (zoid->selected_weapon_mount != zoid->weapon_mount)
            return;
        mount = &zoid->weapon_mounts[zoid->weapon_mount];
        if (mount->active == 0)
            return;
        input = control->field_0140[zoid->weapon_mount];
        if (input == 3 || input == 4) {
            if (zoid->jump_phase != 0)
                return;
            if (zoid->action == 0x1a)
                return;
            if (zoid->action == 0x19)
                return;
            if (zoid->action == 0x17)
                return;
            if (zoid->action == 0x18)
                return;
        }
        state = mount->state;
        if (state == 2 || state == 3 || state == 4 || state == 5) {
            if (state != 3)
                mount->state = 3;
            if (zoid->weapon_mount != WEAPON_MOUNT_SUPER_ATTACK)
                zdWeaponFireVoice(zoid);
            zoid->anim1_frames = 0;
            if (zoid->weapon_mount == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[19] == 0) {
                for (index = 0; index < 10; index++)
                    zdWeaponFire1_(zoid, index);
            } else {
                zdWeaponFire1_(zoid, zoid->weapon_mount);
            }
        }
    }
}
