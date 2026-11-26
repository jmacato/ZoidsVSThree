#include "zoid3.h"

extern void zdSearchTop1(f32 *top, HSD_JObj *joint);

void zdSearchTop(ZoidState *zoid)
{
    f32 top;

    if (zoid != 0 && zoid->joint != 0) {
        top = zoid->position[1];
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->head_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->neck_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->bust_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->hip_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->l_arm1_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->l_arm2_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->r_arm1_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->r_arm2_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->l_leg1_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->l_leg2_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->r_leg1_coobj));
        zdSearchTop1(&top, (*(HSD_JObj **)zoid->r_leg2_coobj));
        zdSearchTop1(&top, zoid->feet[3].joint);
        zdSearchTop1(&top, zoid->feet[2].joint);
        zdSearchTop1(&top, zoid->feet[1].joint);
        zdSearchTop1(&top, zoid->feet[0].joint);
        zoid->field_1AA8 = top;
    }
}
