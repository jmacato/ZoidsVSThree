#include "zoid3.h"

extern s32 vsyncN;
extern s32 HSD_Randi(s32 maximum);
extern void zdCoObjSpark1(ZoidState *zoid, CoObj *co, s32 index);

void zdCoObjSpark(ZoidState *zoid)
{
    u32 phase;
    s32 index;
    s32 tail;

    if (zoid != 0 && zoid->joint != 0 && zoid->stel_state == 0) {
        phase = ((u32)vsyncN / 20) & 0x1F;
        if (HSD_Randi(6) == 0) {
            index = 0;
            zdCoObjSpark1(zoid, (CoObj *)zoid->body_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->head_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->neck_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->bust_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->hip_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->l_arm1_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->l_arm2_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->r_arm1_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->r_arm2_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->l_leg1_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->l_leg2_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->r_leg1_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->r_leg2_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->l_foot_coobj, index);
            index++;
            zdCoObjSpark1(zoid, (CoObj *)zoid->r_foot_coobj, index);
            index++;
            for (tail = 0; tail < 8; tail++) {
                zdCoObjSpark1(zoid, (CoObj *)zoid->tail_coobjs[tail], index);
                index++;
            }
        }
    }
}
