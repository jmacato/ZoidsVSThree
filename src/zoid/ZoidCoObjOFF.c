#include "zoid3.h"

extern void zdCoObjOFF(void *object);

void ZoidCoObjOFF(ZoidState *zoid)
{
    s32 i;

    if (zoid == (void *)0) {
        return;
    }
    if (zoid->joint == (void *)0) {
        return;
    }
    zdCoObjOFF(&zoid->head_coobj);
    zdCoObjOFF(&zoid->neck_coobj);
    zdCoObjOFF(&zoid->bust_coobj);
    zdCoObjOFF(&zoid->hip_coobj);
    for (i = 0; i < 8; i++) {
        zdCoObjOFF(&zoid->tail_coobjs[i]);
    }
    zdCoObjOFF(&zoid->l_arm1_coobj);
    zdCoObjOFF(&zoid->l_arm2_coobj);
    zdCoObjOFF(&zoid->r_arm1_coobj);
    zdCoObjOFF(&zoid->r_arm2_coobj);
    zdCoObjOFF(&zoid->l_leg1_coobj);
    zdCoObjOFF(&zoid->l_leg2_coobj);
    zdCoObjOFF(&zoid->r_leg1_coobj);
    zdCoObjOFF(&zoid->r_leg2_coobj);
    zdCoObjOFF(&zoid->l_foot_coobj);
    zdCoObjOFF(&zoid->r_foot_coobj);
}
