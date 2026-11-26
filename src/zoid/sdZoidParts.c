#include "zoid3.h"

extern void sdDisp1(HSD_JObj *joint);

void sdZoidParts(ZoidState *zoid)
{
    s32 i;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        sdDisp1(*(HSD_JObj **)zoid->head_coobj);
        sdDisp1(*(HSD_JObj **)zoid->neck_coobj);
        sdDisp1(*(HSD_JObj **)zoid->bust_coobj);
        sdDisp1(*(HSD_JObj **)zoid->hip_coobj);
        for (i = 0; i < 8; i++) {
            sdDisp1(*(HSD_JObj **)zoid->tail_coobjs[i]);
        }
        sdDisp1(*(HSD_JObj **)zoid->l_arm1_coobj);
        sdDisp1(*(HSD_JObj **)zoid->l_arm2_coobj);
        sdDisp1(*(HSD_JObj **)zoid->r_arm1_coobj);
        sdDisp1(*(HSD_JObj **)zoid->r_arm2_coobj);
        sdDisp1(*(HSD_JObj **)zoid->l_leg1_coobj);
        sdDisp1(*(HSD_JObj **)zoid->l_leg2_coobj);
        sdDisp1(*(HSD_JObj **)zoid->r_leg1_coobj);
        sdDisp1(*(HSD_JObj **)zoid->r_leg2_coobj);
    }
}
