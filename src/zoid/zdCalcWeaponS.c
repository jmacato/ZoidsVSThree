#include "zoid3.h"
#include "game_part_data.h"

void zdCalcWeaponS(ZoidState *zoid, s32 part)
{
    if (part > 0) {
        PartData *data = &Tea_partsdat[part];
        zoid->field_20C4 += *(s32 *)data->reserved_58;
        zoid->radar_range_bonus += data->radar_range_bonus;
        zoid->search_range_bonus += data->search_range_bonus;
        zoid->armor_bonus += data->armor_bonus;
        zoid->field_20D8 += data->field_E4;
        zoid->speed_bonus += data->speed_bonus;
        zoid->turn_bonus += data->turn_bonus;
        if (data->category == 3) {
            zoid->bullet_power_bonus += data->power;
            zoid->melee_power_bonus += data->power;
        }
        zoid->field_20F4 += data->field_50;
    }
}
