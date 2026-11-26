#pragma readonly_strings on
#include "zoid3.h"
#include "model_archive.h"

extern ModelArchive *dsp1p;
extern s32 gameTime;
extern s32 onTime;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern s32 jobjAnim(HSD_JObj *joint);
extern void HSD_JObjDisp(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

void s1pTimer(HSD_JObj *joint)
{
    HSD_JObj *child;
    s32 time;
    HSD_JObj *from;
    HSD_JObj *timer;
    HSD_JObj *to;
    s32 i;
    s32 digit[4];

    if (gameTime <= 0)
        return;
    if (dsp1p == 0)
        return;
    if (joint == 0)
        return;
    child = GetChild(joint, 0, 8, -1, -1, -1);
    if (child == 0)
        return;
    timer = dsp1p->models[13];
    if (timer == 0)
        return;
    jobjCopyPos(child, timer);
    time = gameTime / 60;
    digit[3] = time % 10;
    time = time / 10;
    digit[2] = time % 6;
    time = time / 6;
    digit[1] = time % 10;
    time = time / 10;
    digit[0] = time % 6;
    time = time / 6;
    if (gameTime == 1800) {
        onTime = 1;
        if (gameTime != 0)
            SetAnimArc2(dsp1p, 13, 1);
    }
    if (gameTime <= 1800 && onTime == 0) {
        onTime = 1;
        if (gameTime != 0)
            SetAnimArc2(dsp1p, 13, 1);
    }
    jobjAnim(timer);
    HSD_JObjDisp(GetChild(timer, 0, -1, -1, -1, -1), 0, 7, 0);
    for (i = 0; i < 4; i++) {
        from = GetChild(timer, 0, 13 - i, -1, -1, -1);
        to = GetChild(timer, 0, digit[i], -1, -1, -1);
        jobjCopyPos(from, to);
        HSD_JObjDisp(to, 0, 7, 0);
    }
}
