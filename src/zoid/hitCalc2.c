#include "zoid3.h"

extern s32 hitCalcEasy(ZoidState *zoid, s32 damage);

s32 hitCalc2(ZoidState *attacker, s32 damage, ZoidState *target)
{
    if (attacker == 0)
        return damage;
    if (target == 0)
        return damage;
    if (attacker->joint == 0)
        return damage;
    if (target->joint == 0)
        return damage;
    damage -= target->armor;
    damage = hitCalcEasy(target, damage);
    if (damage < 10)
        damage = 10;
    return damage;
}
