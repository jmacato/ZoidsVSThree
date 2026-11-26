#include "zoid3.h"

typedef struct ZoidDataVS3 {
    u8 pad_0000[0x98];
    s16 option_two;
    u8 pad_009A[0x7FC - 0x9A];
} ZoidDataVS3;

typedef struct ZoidAnimDataVS3 {
    u8 pad_0000[0xF8];
    s32 field_00F8;
} ZoidAnimDataVS3;

extern ZoidDataVS3 Tea_zoiddat[];
extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);

void zdLoadOption2(ZoidState *zoid, s32 part)
{
    s32 slot;
    ZoidAnimDataVS3 *anim;
    s32 type;

    if (zoid == 0) {
        return;
    }
    anim = zoid->anim_data;
    if (anim == 0) {
        return;
    }
    type = zoid->type;
    slot = Tea_zoiddat[type].option_two;
    if (slot <= 27) {
        zoid->option_type = ZOID_OPTION_BOOSTER;
        zoid->option_energy_max = 2000;
        zoid->option_energy = 0;
        zoid->option_start_cost = 500;
        zoid->option_hold_cost = 2;
        zoid->option_recharge = 6;
        if (anim->field_00F8 == 3) {
            zoid->option_energy_max = 1600;
            zoid->option_energy = 0;
            zoid->option_start_cost = 500;
            zoid->option_hold_cost = 2;
            zoid->option_recharge = 6;
        }
        sWeaponMount(part, zoid, slot, WEAPON_MOUNT_BOOSTER);
    }
}
