#include "zoid3.h"

extern void zdCalcPre(ZoidState *zoid);
extern void zdCalcEpi(ZoidState *zoid);
extern void zdCalcWeapon(ZoidState *zoid, s32 weapon);
extern void zdCalcWeaponS(ZoidState *zoid, s32 part);
extern void zdCalcMan(ZoidState *zoid, s32 person);
extern void OSReport(const char *, ...);

void zdCalc(ZoidState *zoid)
{
    s32 i;

    if (zoid != 0 && zoid->joint != 0) {
        zdCalcPre(zoid);
        for (i = 0; i < 30; i++) {
            if (zoid->weapon_slots[i].joint != 0 && zoid->weapon_slots[i].weapon != -1) {
                zdCalcWeapon(zoid, zoid->weapon_slots[i].weapon);
            }
        }
        for (i = 0; i < 3; i++) {
            zdCalcWeaponS(zoid, zoid->additional_parts[i]);
        }
        if (zoid->field_1EA0 > 0) {
            zdCalcWeaponS(zoid, zoid->field_1EA0);
        }
        zdCalcMan(zoid, zoid->person);
        zdCalcEpi(zoid);
        OSReport("add power z%d \222e=%d , \212i\223\254=%d bp=%d \n", zoid->index,
                 zoid->bullet_power_bonus, zoid->melee_power_bonus, zoid->field_20F8);
    }
}
