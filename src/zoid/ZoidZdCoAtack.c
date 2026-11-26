#include "zoid3.h"

extern s32 zdZdCoAtk(CoObj *co, ZoidAttackObject *attack, s32 effect, s32 flags);
extern s32 sTouchCube(HSD_JObj *a, HSD_JObj *b);

s32 ZoidZdCoAtack(ZoidAttackObject *attack, ZoidState *zoid, s32 effect, s32 flags)
{
    s32 i;

    if (attack == (void *)0) {
        return 0;
    }
    if (attack->joint == (void *)0) {
        return 0;
    }
    if (zoid == (void *)0) {
        return 0;
    }
    if (zoid->joint == (void *)0) {
        return 0;
    }
    if (sTouchCube(*(HSD_JObj **)zoid->body_coobj, attack->joint) == 0) {
        return 0;
    }
    if (zdZdCoAtk((CoObj *)&zoid->head_coobj, attack, effect, flags) != 0) {
        return 1;
    }
    if (zdZdCoAtk((CoObj *)&zoid->neck_coobj, attack, effect, flags) != 0) {
        return 1;
    }
    if (zdZdCoAtk((CoObj *)&zoid->bust_coobj, attack, effect, flags) != 0) {
        return 1;
    }
    if (zdZdCoAtk((CoObj *)&zoid->hip_coobj, attack, effect, flags) != 0) {
        return 1;
    }
    for (i = 0; i < 8; i++) {
        if (zdZdCoAtk((CoObj *)zoid->tail_coobjs[i], attack, effect, flags) != 0) {
            return 2;
        }
    }
    if (zdZdCoAtk((CoObj *)&zoid->l_arm1_coobj, attack, effect, flags) != 0) {
        return 2;
    }
    if (zdZdCoAtk((CoObj *)&zoid->r_arm1_coobj, attack, effect, flags) != 0) {
        return 2;
    }
    if (zdZdCoAtk((CoObj *)&zoid->l_leg1_coobj, attack, effect, flags) != 0) {
        return 2;
    }
    if (zdZdCoAtk((CoObj *)&zoid->r_leg1_coobj, attack, effect, flags) != 0) {
        return 2;
    }
    return 0;
}
