#include "zoid3.h"

extern void zdOptionUseOK(ZoidState *zoid);
extern void zdOptionUse(ZoidState *zoid);
extern void zdOptionUseOnOff(ZoidState *zoid, s32 on);

#define OPTION_ON(zoid) (*(s8 *)&(zoid)->option_use_state)
#define OPTION_PREV(zoid) (*(s8 *)&(zoid)->option_use_previous)

void zdOptionLoop(ZoidState *zoid)
{
    void *ai;
    s32 add;
    void *control;

    ai = zoid->ai;
    zoid->option_active = 0;
    control = zoid->anim_data;
    if (zoid->option_energy_max == 0)
        return;
    if (zoid->super_attack_input != 0)
        OPTION_ON(zoid) = 0;
    if (zoid->option_energy < 0)
        zoid->option_energy = 0;
    zdOptionUseOK(zoid);
    if (ai != 0 && *(s32 *)((u8 *)ai + 0x94) != 0)
        OPTION_ON(zoid) = 1;
    if (zoid->death_started != 0)
        OPTION_ON(zoid) = 0;
    if (OPTION_ON(zoid) != 0) {
        if (zoid->option_energy == 0)
            OPTION_ON(zoid) = 0;
        if (OPTION_PREV(zoid) == 0 && zoid->option_energy_max != zoid->option_energy)
            OPTION_ON(zoid) = 0;
        if (OPTION_ON(zoid) == 0 && ai != 0 && *(s32 *)((u8 *)ai + 0x94) != 0)
            *(s32 *)((u8 *)ai + 0x94) = 0;
    }
    if (OPTION_ON(zoid) != 0) {
        if (OPTION_PREV(zoid) != 0)
            zoid->option_energy -= zoid->option_hold_cost;
        else
            zoid->option_energy -= zoid->option_start_cost;
        zdOptionUse(zoid);
    } else {
        add = zoid->option_recharge;
        if (*(s32 *)((u8 *)zoid + 0x190) != 0 && *(s32 *)((u8 *)zoid + 0x18C) == 0)
            add /= 2;
        if (add == 0 && zoid->option_recharge != 0)
            add = 1;
        zoid->option_energy += add;
        if (zoid->option_energy >= zoid->option_energy_max)
            zoid->option_energy = zoid->option_energy_max;
    }
    zdOptionUseOnOff(zoid, OPTION_ON(zoid));
    OPTION_PREV(zoid) = OPTION_ON(zoid);
}
