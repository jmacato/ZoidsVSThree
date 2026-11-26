#include "zoid3.h"

extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);

void zdLoadOption4(ZoidState *zoid)
{
    zoid->option_type = ZOID_OPTION_SMOKE;
    zoid->option_energy_max = 300;
    zoid->option_energy = 0;
    zoid->option_start_cost = 60;
    zoid->option_hold_cost = 3;
    zoid->option_recharge = 1;
    sWeaponMount(277, zoid, 11, WEAPON_MOUNT_SMOKE_MINE);
}
