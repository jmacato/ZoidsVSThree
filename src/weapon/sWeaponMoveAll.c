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

extern void sWeaponMove(WeaponState3 *weapon);

void sWeaponMoveAll(void)
{
    WeaponState3 *weapon;
    s32 index;

    for (index = 0; index < 100; index++) {
        weapon = &sWeapon[index];
        if (weapon->active != 0) {
            sWeaponMove(weapon);
        }
    }
}
