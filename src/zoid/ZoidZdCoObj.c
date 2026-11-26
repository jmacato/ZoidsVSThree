#include "zoid3.h"

extern s32 zdCoObj(ZoidState *zoid, CoObj *co);
extern s32 sTouchCube(HSD_JObj *a, HSD_JObj *b);
extern u32 bitTBL[];

s32 ZoidZdCoObj(ZoidState *zoid, ZoidState *other)
{
    s32 hit;
    s32 i;
    s32 secondary_hit;

    if (zoid == (void *)0) {
        return 0;
    }
    if (zoid->joint == (void *)0) {
        return 0;
    }
    if (other == (void *)0) {
        return 0;
    }
    if (other->joint == (void *)0) {
        return 0;
    }
    if (sTouchCube(*(HSD_JObj **)zoid->body_coobj, *(HSD_JObj **)other->body_coobj) == 0) {
        return 0;
    }
    zoid->contact_bits |= bitTBL[other->index];
    other->contact_bits |= bitTBL[zoid->index];
    /* The release code discards secondary contact results. */
    secondary_hit = 0;
    hit = 0;
    if (zdCoObj(zoid, (CoObj *)&other->head_coobj)) {
        secondary_hit = 1;
    }
    for (i = 0; i < 8; i++) {
        if (zdCoObj(zoid, (CoObj *)other->tail_coobjs[i])) {
            secondary_hit = 1;
        }
    }
    if (zdCoObj(zoid, (CoObj *)&other->l_arm2_coobj)) {
        secondary_hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->r_arm2_coobj)) {
        secondary_hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->l_leg2_coobj)) {
        secondary_hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->r_leg2_coobj)) {
        secondary_hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->neck_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->bust_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->hip_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->l_arm1_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->r_arm1_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->l_leg1_coobj) != 0) {
        hit = 1;
    }
    if (zdCoObj(zoid, (CoObj *)&other->r_leg1_coobj) != 0) {
        hit = 1;
    }
    return hit;
}
