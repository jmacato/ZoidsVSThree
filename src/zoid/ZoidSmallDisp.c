#include "zoid3.h"

extern void zdCoSmallDisp(void *object);

void ZoidSmallDisp(ZoidState *zoid)
{
    s32 i;

    if (zoid == (void *)0) {
        return;
    }
    if (zoid->joint == (void *)0) {
        return;
    }
    zdCoSmallDisp(&zoid->head_coobj);
    zdCoSmallDisp(&zoid->neck_coobj);
    zdCoSmallDisp(&zoid->bust_coobj);
    zdCoSmallDisp(&zoid->hip_coobj);
    for (i = 0; i < 8; i++) {
        zdCoSmallDisp(&zoid->tail_coobjs[i]);
    }
    zdCoSmallDisp(&zoid->l_arm1_coobj);
    zdCoSmallDisp(&zoid->l_arm2_coobj);
    zdCoSmallDisp(&zoid->r_arm1_coobj);
    zdCoSmallDisp(&zoid->r_arm2_coobj);
    zdCoSmallDisp(&zoid->l_leg1_coobj);
    zdCoSmallDisp(&zoid->l_leg2_coobj);
    zdCoSmallDisp(&zoid->r_leg1_coobj);
    zdCoSmallDisp(&zoid->r_leg2_coobj);
    zdCoSmallDisp(&zoid->l_foot_coobj);
    zdCoSmallDisp(&zoid->r_foot_coobj);
}
