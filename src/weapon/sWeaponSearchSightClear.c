#include "types.h"

typedef struct WeaponSightEntry3 {
    s32 value;
    u8 reserved_04[0x20];
} WeaponSightEntry3;

typedef struct WeaponState3 {
    u8 reserved_0000[0x428];
    WeaponSightEntry3 sights[20];
} WeaponState3;

void sWeaponSearchSightClear(WeaponState3 *weapon)
{
    s32 i;

    for (i = 0; i < 20; i++) {
        weapon->sights[i].value = 0;
    }
}
