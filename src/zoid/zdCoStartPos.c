#include "zoid3.h"

extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void ZoidCoBAK(ZoidState *zoid, void *object);

void zdCoStartPos(ZoidState *zoid)
{
    s32 axis;

    zdSetXYZ(zoid);
    sMakeMatrix(zoid->joint);
    ZoidCoBAK(zoid, zoid->body_coobj);
    ZoidCoBAK(zoid, zoid->head_coobj);
    ZoidCoBAK(zoid, zoid->neck_coobj);
    ZoidCoBAK(zoid, zoid->bust_coobj);
    ZoidCoBAK(zoid, zoid->hip_coobj);
    ZoidCoBAK(zoid, zoid->tail_coobjs[0]);
    ZoidCoBAK(zoid, zoid->l_arm1_coobj);
    ZoidCoBAK(zoid, zoid->r_arm1_coobj);
    ZoidCoBAK(zoid, zoid->l_leg1_coobj);
    ZoidCoBAK(zoid, zoid->r_leg1_coobj);
    ZoidCoBAK(zoid, zoid->l_arm2_coobj);
    ZoidCoBAK(zoid, zoid->r_arm2_coobj);
    ZoidCoBAK(zoid, zoid->l_leg2_coobj);
    ZoidCoBAK(zoid, zoid->r_leg2_coobj);
    for (axis = 0; axis < 3; axis++) {
        zoid->field_1C24[axis] = zoid->position[axis];
        zoid->previous_position[axis] = zoid->position[axis];
    }
}
