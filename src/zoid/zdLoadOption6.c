#include "zoid3.h"

typedef struct ZoidDataVS3 {
    u8 pad_0000[0xA0];
    s16 option_two;
    u8 pad_00A2[0x7FC - 0xA2];
} ZoidDataVS3;

extern ZoidDataVS3 Tea_zoiddat[];
extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);

void zdLoadOption6(ZoidState *zoid, s32 part)
{
    s32 type = zoid->type;
    s32 slot = Tea_zoiddat[type].option_two;

    if (slot <= 27) {
        zoid->option_type = 6;
        zoid->option_energy_max = 2000;
        zoid->option_energy = 0;
        zoid->option_start_cost = 500;
        zoid->option_hold_cost = 2;
        zoid->option_recharge = 6;
        sWeaponMount(part, zoid, slot, WEAPON_MOUNT_BOOSTER);
    }
}
