#include "zoid3.h"

void zdLoadOption3(ZoidState *zoid)
{
    zoid->option_type = ZOID_OPTION_CAMOUFLAGE;
    zoid->option_energy_max = 2000;
    zoid->option_energy = 0;
    zoid->option_start_cost = 500;
    zoid->option_hold_cost = 1;
    zoid->option_recharge = 3;
}
