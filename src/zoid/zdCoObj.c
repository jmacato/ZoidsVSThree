#include "zoid3.h"

extern s32 ZoidCoObjCoObj(CoObj *a, CoObj *b, s32 flags);

s32 zdCoObj(ZoidState *zoid, CoObj *obj)
{
    s32 i;
    s32 secondary_hit;
    s32 hit;

    if (zoid == (void *)0)
        return 0;
    if (zoid->joint == (void *)0)
        return 0;
    if (obj == (void *)0)
        return 0;
    if (obj->joint == (void *)0)
        return 0;
    /* The release code discards secondary contact results. */
    secondary_hit = 0;
    hit = 0;
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->head_coobj, 1)) {
        secondary_hit = 1;
    }
    for (i = 0; i < 8; i++) {
        if (ZoidCoObjCoObj(obj, (CoObj *)zoid->tail_coobjs[i], 1)) {
            secondary_hit = 1;
        }
    }
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->l_arm2_coobj, 1)) {
        secondary_hit = 1;
    }
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->r_arm2_coobj, 1)) {
        secondary_hit = 1;
    }
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->l_leg2_coobj, 1)) {
        secondary_hit = 1;
    }
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->r_leg2_coobj, 1)) {
        secondary_hit = 1;
    }
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->neck_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->bust_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->hip_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->l_arm1_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->r_arm1_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->l_leg1_coobj, 1) != 0)
        hit = 1;
    if (ZoidCoObjCoObj(obj, (CoObj *)zoid->r_leg1_coobj, 1) != 0)
        hit = 1;
    return hit;
}
