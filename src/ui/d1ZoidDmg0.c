#include "zoid_collision.h"

extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 a, s32 b, s32 c);

void d1ZoidDmg0(HSD_JObj *joint, s32 index, CoDamage *damage)
{
    f32 ratio;
    s32 level;
    HSD_JObj *child;
    s32 health;

    if (joint != (void *)0 && damage != (void *)0) {
        health = damage->health;
        if (damage->maximum_health != 0) {
            ratio = 100.0 * health / damage->maximum_health;
        } else {
            return;
        }
        level = 0;
        if (ratio < 50.0f) {
            level = 1;
        }
        if (ratio < 1.0f) {
            level = 2;
        }
        if (level == 0) {
            child = GetChild(joint, 0, index, -1, -1, -1);
        }
        if (level == 1) {
            child = GetChild(joint, 0, index, 0, -1, -1);
        }
        if (level == 2) {
            child = GetChild(joint, 0, index, 0, 0, -1);
        }
        if (child != (void *)0) {
            HSD_JObjDisp(child, 0, 7, 0);
        }
    }
}
