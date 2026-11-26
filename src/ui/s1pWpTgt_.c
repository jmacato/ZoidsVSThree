#include "zoid3.h"
#include "game_camera.h"
#include "missile.h"

typedef struct WeaponState3 {
    s32 active;
    u32 flags;
    u32 state_flags;
    u8 reserved_0C[0x3E8 - 0x0C];
    s32 animation;
    s32 ammo;
    u8 reserved_3F0[0x3FC - 0x3F0];
    s32 bullet_kind;
    s32 field_0400;
    u8 reserved_404[0x6DC - 0x404];
} WeaponState3;

extern WeaponState3 sWeapon[100];
extern void s1pWp1TgtStraight(CameraState *disp, WeaponState3 *weapon, f32 distance);
extern void s1pWp1TgtHome(CameraState *disp, WeaponState3 *weapon);
extern void s1pWp1TgtParabola(CameraState *disp, WeaponState3 *weapon, f32 distance);

void s1pWpTgt_(CameraState *disp, ZoidState *zoid, s32 mount)
{
    u8 target_slot;
    s32 i;
    WeaponState3 *weapon;
    f32 distance;
    s32 slot;
    s32 index;

    WeaponMount *wm = &zoid->weapon_mounts[mount];
    if (wm->active == 0)
        return;
    distance = 0.0f;
    target_slot = zoid->target_slot;
    if (target_slot == -1)
        zoid->target_pending = 0;
    if (zoid->target_pending != 0)
        distance = zoid->distances[zoid->target_slot];
    if (zoid->lock_active != 0)
        distance = zoid->field_1E8C;
    for (i = 0; i < 4; i++) {
        if (wm->entries[i].active == 0)
            continue;
        slot = wm->entries[i].slot;
        if (slot == -1)
            continue;
        index = zoid->weapon_slots[slot].weapon;
        if (index == -1)
            continue;
        weapon = &sWeapon[index];
        if (weapon->field_0400 == 0)
            continue;
        switch (weapon->bullet_kind) {
        case 0:
        case 6:
            s1pWp1TgtStraight(disp, weapon, distance);
            break;
        case 1:
            s1pWp1TgtHome(disp, weapon);
            break;
        case 2:
            s1pWp1TgtParabola(disp, weapon, distance);
            break;
        }
    }
}
