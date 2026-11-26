#include "zoid3.h"
#include "game_part_data.h"
#include "game_person_data.h"

void zdCalcMan(ZoidState *zoid, s32 person)
{
    if (zoid != 0 && person >= 0) {
        PersonData *pilot = &Tea_persondat[person];
        zoid->turn_bonus += pilot->turn_bonus;
        zoid->melee_power_bonus += pilot->melee_power_bonus;
        zoid->bullet_power_bonus += pilot->bullet_power_bonus;
    }
}
