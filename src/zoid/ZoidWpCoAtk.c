#include "zoid3.h"

extern s32 zdWpCoAtk(void *object, ZoidAttackObject *target, s32 kind, s32 damage);
extern s32 sTouchCube(HSD_JObj *a, HSD_JObj *b);

s32 ZoidWpCoAtk(ZoidAttackObject *attack, ZoidState *zoid, s32 effect, s32 damage)
{
    s32 i;
    s32 amount;
    f32 ratio;

    if (attack == (void *)0)
        return 0;
    if (attack->joint == (void *)0)
        return 0;
    if (zoid == (void *)0)
        return 0;
    if (zoid->joint == (void *)0)
        return 0;
    if (sTouchCube(*(HSD_JObj **)zoid->body_coobj, attack->joint) == 0)
        return 0;
    if (zoid->armor < 1)
        zoid->armor = 1;
    ratio = 10.0 * (f32)damage / (f32)zoid->armor;
    amount = ratio;
    if (zdWpCoAtk(&zoid->head_coobj, attack, effect, amount) != 0)
        return 1;
    if (zdWpCoAtk(&zoid->neck_coobj, attack, effect, amount) != 0)
        return 1;
    if (zdWpCoAtk(&zoid->bust_coobj, attack, effect, amount) != 0)
        return 1;
    if (zdWpCoAtk(&zoid->hip_coobj, attack, effect, amount) != 0)
        return 1;
    for (i = 0; i < 8; i++) {
        if (zdWpCoAtk(&zoid->tail_coobjs[i], attack, effect, amount) != 0)
            return 1;
    }
    if (zdWpCoAtk(&zoid->l_arm1_coobj, attack, effect, amount) != 0)
        return 1;
    if (zdWpCoAtk(&zoid->r_arm1_coobj, attack, effect, amount) != 0)
        return 1;
    if (zdWpCoAtk(&zoid->l_leg1_coobj, attack, effect, amount) != 0)
        return 1;
    if (zdWpCoAtk(&zoid->r_leg1_coobj, attack, effect, amount) != 0)
        return 1;
    return 0;
}
