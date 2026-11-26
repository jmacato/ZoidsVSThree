#include "zoid3.h"

extern void sWeaponMount(s32 part, ZoidState *zoid, s32 slot, s32 mount);

void zdLoadOption5(ZoidState *zoid)
{
    zoid->option_type = ZOID_OPTION_MINE;
    zoid->option_energy_max = 500;
    zoid->option_energy = 0;
    zoid->option_start_cost = 500;
    zoid->option_hold_cost = 10;
    zoid->option_recharge = 1;
    sWeaponMount(399, zoid, 11, WEAPON_MOUNT_SMOKE_MINE);
}
