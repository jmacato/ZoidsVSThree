#include "zoid3.h"
#include "weapon.h"
#include "missile.h"
#include "game_camera.h"

extern void s1pWpTgt_(CameraState *disp, ZoidState *zoid, s32 mount);

void s1pWpTgt(CameraState *disp, ZoidState *zoid)
{
    s32 i;

    *(s32 *)((u8 *)disp + 0x588) = 0;
    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    if (zoid->death_started != 0)
        return;
    if (zoid->weapon_mount == -1)
        return;
    if (zoid->selected_weapon_mount == -1)
        return;
    if (zoid->selected_weapon_mount != zoid->weapon_mount)
        return;
    if (zoid->selected_weapon_mount == WEAPON_MOUNT_SUPER_ATTACK && zoid->mount_has_weapon[WEAPON_MOUNT_SUPER_ATTACK] == 0) {
        for (i = 0; i < 10; i++)
            s1pWpTgt_(disp, zoid, i);
    } else {
        s1pWpTgt_(disp, zoid, zoid->selected_weapon_mount);
    }
}
