#include "zoid3.h"

extern s32 hitCalcEasy(ZoidState *zoid, s32 damage);

s32 hitCalc(ZoidState *attacker, s32 damage, ZoidState *defender)
{
    if (attacker == 0)
        return damage;
    if (defender == 0)
        return damage;
    if (attacker->joint == 0)
        return damage;
    if (defender->joint == 0)
        return damage;
    damage += attacker->melee_power_bonus;
    damage -= defender->armor;
    damage = hitCalcEasy(defender, damage);
    if (damage < 10)
        damage = 10;
    return damage;
}
