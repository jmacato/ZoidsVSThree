#include "zoid3.h"

extern void dummyFunc(const char *);
extern void zdSearchTop(ZoidState *zoid);
extern void zdGrdCoON(ZoidState *zoid, CoObj *co, s32 flag);

void ZoidGrdON(ZoidState *zoid)
{
    ZoidControlData *control;

    control = (ZoidControlData *)zoid->anim_data;
    if (control != 0 && zoid != (void *)0 && zoid->joint != (void *)0) {
        zoid->grounded = 0;
        zoid->max_ground_depth = 0.0f;
        zdSearchTop(zoid);
        dummyFunc("0");
        zdGrdCoON(zoid, (CoObj *)zoid->body_coobj, 0);
        dummyFunc("9");
        zdGrdCoON(zoid, (CoObj *)zoid->head_coobj, control->ground_modes[0] >= 2);
        dummyFunc("8");
        zdGrdCoON(zoid, (CoObj *)zoid->neck_coobj, control->ground_modes[1] >= 2);
        dummyFunc("7");
        zdGrdCoON(zoid, (CoObj *)zoid->bust_coobj, 1);
        dummyFunc("6");
        zdGrdCoON(zoid, (CoObj *)zoid->hip_coobj, 1);
        dummyFunc("1");
        zdGrdCoON(zoid, (CoObj *)zoid->l_arm1_coobj, 1);
        zdGrdCoON(zoid, (CoObj *)zoid->r_arm1_coobj, 1);
        zdGrdCoON(zoid, (CoObj *)zoid->l_leg1_coobj, 1);
        zdGrdCoON(zoid, (CoObj *)zoid->r_leg1_coobj, 1);
        dummyFunc("2");
        zdGrdCoON(zoid, (CoObj *)zoid->l_arm2_coobj, 0);
        zdGrdCoON(zoid, (CoObj *)zoid->r_arm2_coobj, 0);
        zdGrdCoON(zoid, (CoObj *)zoid->l_leg2_coobj, 0);
        zdGrdCoON(zoid, (CoObj *)zoid->r_leg2_coobj, 0);
        dummyFunc("3");
        if (zoid->grounded != 0) {
            zoid->grounded_frames++;
        } else {
            zoid->grounded_frames = 0;
        }
        dummyFunc("4");
    }
}
