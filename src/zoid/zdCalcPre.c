#include "zoid3.h"

void zdCalcPre(ZoidState *zoid)
{
    zoid->field_20C0 = 0;
    zoid->field_20C4 = 0;
    zoid->radar_range_bonus = 0;
    zoid->search_range_bonus = 0;
    zoid->field_20D0 = 0;
    zoid->armor_bonus = 0;
    zoid->field_20D8 = 0;
    zoid->speed_bonus = 0;
    zoid->bullet_power_bonus = 0;
    zoid->melee_power_bonus = 0;
    zoid->turn_bonus = 0;
    zoid->field_20F4 = 0;
}
