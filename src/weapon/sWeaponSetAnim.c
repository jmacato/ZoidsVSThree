#include "types.h"

typedef struct WeaponState3 {
    s32 active;
    u32 flags;
    u32 state_flags;
    u8 reserved_0C[0x3E8 - 0x0C];
    s32 animation;
    s32 ammo;
    u8 reserved_3F0[0x6DC - 0x3F0];
} WeaponState3;

extern WeaponState3 sWeapon[100];
extern void sWeaponSetAnimWp(WeaponState3 *weapon, s32 animation);

void sWeaponSetAnim(s32 index, s32 animation)
{
    WeaponState3 *weapon;

    if (index < 0) {
        return;
    }
    if (index >= 100) {
        return;
    }
    weapon = &sWeapon[index];
    sWeaponSetAnimWp(weapon, animation);
}
