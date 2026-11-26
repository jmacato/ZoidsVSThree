#include "zoid3.h"

extern s32 sZoidEx;
extern void setCoDmg2(void *first, void *second, CoDamage *damage);

void zdCalcCoDmg(ZoidState *zoid)
{
    f32 ratio;

    setCoDmg2(zoid->head_coobj, zoid->neck_coobj, &zoid->damages[0]);
    setCoDmg2(zoid->bust_coobj, zoid->hip_coobj, &zoid->damages[1]);
    setCoDmg2(zoid->l_arm1_coobj, zoid->l_arm2_coobj, &zoid->damages[2]);
    setCoDmg2(zoid->r_arm1_coobj, zoid->r_arm2_coobj, &zoid->damages[3]);
    setCoDmg2(zoid->l_leg1_coobj, zoid->l_leg2_coobj, &zoid->damages[4]);
    setCoDmg2(zoid->r_leg1_coobj, zoid->r_leg2_coobj, &zoid->damages[5]);
    if (zoid->max_health <= 0) {
        zoid->max_health = 0;
        zoid->super_attack_enabled = 0;
    } else {
        ratio = (f32)zoid->health / (f32)zoid->max_health;
        zoid->super_attack_enabled = ratio < 0.3333333;
    }
    if (sZoidEx != 0) {
        zoid->super_attack_enabled = 1;
        if (zoid->super_attack_cooldown > 60) {
            zoid->super_attack_cooldown = 60;
        }
    }
}
