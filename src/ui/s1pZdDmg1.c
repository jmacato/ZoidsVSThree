#include "zoid3.h"

typedef struct S1pDisplay {
    u8 reserved_00[0x3C];
    HSD_JObj *damage_joint;
} S1pDisplay;

extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 a, s32 b, s32 c);
extern void d1ZoidDmg0(HSD_JObj *joint, s32 index, CoDamage *damage);

void s1pZdDmg1(ZoidState *zoid, S1pDisplay *display, HSD_JObj *parent)
{
    HSD_JObj *child;

    if (display->damage_joint != (void *)0 && parent != (void *)0) {
        child = GetChild(parent, 0, 0, -1, -1, -1);
        if (child != (void *)0) {
            jobjCopyPos(child, display->damage_joint);
            HSD_JObjDisp(display->damage_joint, 0, 7, 0);
            d1ZoidDmg0(display->damage_joint, 0, &zoid->damages[0]);
            d1ZoidDmg0(display->damage_joint, 1, &zoid->damages[1]);
            d1ZoidDmg0(display->damage_joint, 2, &zoid->damages[3]);
            d1ZoidDmg0(display->damage_joint, 3, &zoid->damages[2]);
            d1ZoidDmg0(display->damage_joint, 4, &zoid->damages[5]);
            d1ZoidDmg0(display->damage_joint, 5, &zoid->damages[4]);
        }
    }
}
