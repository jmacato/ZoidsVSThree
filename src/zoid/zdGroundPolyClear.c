#include "zoid3.h"

extern void zdGroundCoPolyClear(ZoidState *zoid, void *object);

void zdGroundPolyClear(ZoidState *zoid)
{
    s32 part;

    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->body_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->bust_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->neck_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->head_coobj));
    for (part = 0; part < 8; part++)
        zdGroundCoPolyClear(zoid, &zoid->tail_coobjs[part]);
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->hip_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->l_arm1_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->r_arm1_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->l_leg1_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->r_leg1_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->l_arm2_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->r_arm2_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->l_leg2_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->r_leg2_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->l_foot_coobj));
    zdGroundCoPolyClear(zoid, &(*(HSD_JObj **)zoid->r_foot_coobj));
}
