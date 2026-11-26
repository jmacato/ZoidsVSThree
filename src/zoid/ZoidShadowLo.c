#include "zoid3.h"

extern s32 zdShadowLo(void *shadow, void *co);
extern void zdShadowLoChk(void *shadow, void *co);

void ZoidShadowLo(void *shadow, ZoidState *zoid)
{
    s32 i;

    if (shadow != 0 && zoid->joint != (void *)0) {
        if (zdShadowLo(shadow, zoid->bust_coobj) != 0) {
            if (zdShadowLo(shadow, zoid->neck_coobj) != 0) {
                zdShadowLo(shadow, zoid->head_coobj);
            }
        }
        zdShadowLo(shadow, zoid->hip_coobj);
        for (i = 0; i < 8; i++) {
            zdShadowLo(shadow, zoid->tail_coobjs[i]);
        }
        zdShadowLo(shadow, zoid->l_arm1_coobj);
        zdShadowLo(shadow, zoid->l_arm2_coobj);
        zdShadowLo(shadow, zoid->r_arm1_coobj);
        zdShadowLo(shadow, zoid->r_arm2_coobj);
        zdShadowLo(shadow, zoid->l_leg1_coobj);
        zdShadowLo(shadow, zoid->l_leg2_coobj);
        zdShadowLo(shadow, zoid->r_leg1_coobj);
        zdShadowLo(shadow, zoid->r_leg2_coobj);
        zdShadowLoChk(shadow, zoid->l_foot_coobj);
        zdShadowLoChk(shadow, zoid->r_foot_coobj);
    }
}
