#include "zoid3.h"
#include "game_mode.h"

extern s32 zdWeaponChg0(ZoidState *zoid);
extern void zdWeaponSightClearAll(ZoidState *zoid);
extern s32 camSe(void *camera, s16 sound, Vec3 *point);

void zdWeaponChg(ZoidState *zoid)
{
    s32 index;
    s32 prev;
    s32 play;

    if (zoid == (void *)0)
        return;
    if (zoid->joint == (void *)0)
        return;
    if (zoid->death_started != 0)
        return;
    prev = zoid->weapon_mount;
    zoid->weapon_mount_count = zdWeaponChg0(zoid);
    if (zoid->weapon_mount_count < 1)
        return;
    if (zoid->weapon_mount_count > 0) {
        for (index = 0; index < 10; index++) {
            zoid->selected_weapon_mount++;
            if (zoid->selected_weapon_mount > 9)
                zoid->selected_weapon_mount = 0;
            if (zoid->weapon_mounts[zoid->selected_weapon_mount].active != 0)
                break;
        }
    }
    if (zoid->selected_weapon_mount == -1)
        return;
    if (prev == zoid->selected_weapon_mount) {
        if (zoid->ai_active != 0)
            return;
        if (zoid->weapon_mount_count > 1)
            return;
        zoid->selected_weapon_mount = -1;
    }
    play = 1;
    if (GameMode.game_type == 9)
        play = 0;
    if (zoid->camera == 0)
        play = 0;
    if (zoid->ai != 0 && zoid->ai_active != 0)
        play = 0;
    if (play != 0)
        camSe(zoid->camera, 0x5b, (Vec3 *)&zoid->position);
    zdWeaponSightClearAll(zoid);
}
