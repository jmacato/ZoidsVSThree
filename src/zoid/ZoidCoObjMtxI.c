#include "zoid3.h"
#include "matrix.h"

extern void zdCoObjMtxI(void *object);
extern u32 PSMTXInverse(Mtx source, Mtx destination);

void ZoidCoObjMtxI(ZoidState *zoid)
{
    s32 i;
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        zdCoObjMtxI(zoid->body_coobj);
        zdCoObjMtxI(zoid->bust_coobj);
        zdCoObjMtxI(zoid->neck_coobj);
        zdCoObjMtxI(zoid->head_coobj);
        zdCoObjMtxI(zoid->hip_coobj);
        for (i = 0; i < 8; i++)
            zdCoObjMtxI(zoid->tail_coobjs[i]);
        zdCoObjMtxI(zoid->l_arm1_coobj);
        zdCoObjMtxI(zoid->r_arm1_coobj);
        zdCoObjMtxI(zoid->l_arm2_coobj);
        zdCoObjMtxI(zoid->r_arm2_coobj);
        zdCoObjMtxI(zoid->l_leg1_coobj);
        zdCoObjMtxI(zoid->l_leg2_coobj);
        zdCoObjMtxI(zoid->r_leg1_coobj);
        zdCoObjMtxI(zoid->r_leg2_coobj);
        for (i = 0; i < 10; i++) {
            ZoidAttackObject *attack = &zoid->attack_objects[i];
            if (attack->joint != (void *)0)
                PSMTXInverse(attack->joint->matrix, attack->inverse);
        }
    }
}
