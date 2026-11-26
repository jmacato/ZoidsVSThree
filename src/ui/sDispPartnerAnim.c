#pragma readonly_strings on
#pragma auto_inline off
#include "zoid3.h"
#include "model_archive.h"
#include "game_mode.h"

extern ModelArchive *dspPartner;
extern s32 sCamNN;
extern s32 gameEndF;
extern s32 dspPartnerMsg;
extern s32 dspPartnerMsgA;
extern s32 dspPartnerMsgB;
extern s32 dspPartnerMsgF;
extern s32 dspPartnerMsgM;
extern s32 dspPartnerMsgTm;
extern s32 dspPartnerMsgV;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern s32 jobjAnim(HSD_JObj *joint);
extern void zdVoiceScG(ZoidState *zoid, s32 voice);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, u32 line, const char *condition);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & 0x00800000) && (jobj->flags & 0x40);
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj)
{
    if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
        HSD_JObjSetMtxDirtySub(jobj);
}

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & 0x02000000))
        HSD_JObjSetMtxDirty(jobj);
}

void sDispPartnerAnim(void *arg)
{
    s32 GetChild_first;

    register s32 i;
    HSD_JObj *bar;
    HSD_JObj *root;
    ZoidState *partner;
    s32 anim;
    f32 max;
    f32 ratio;

    if (*(s32 *)((u8 *)&GameMode + 0x44) != 0)
        return;
    if (sCamNN != 1)
        return;
    if (dspPartner == 0)
        return;
    if (gameEndF > 3)
        return;
    partner = &Zoid[2];
    if (partner->joint == (void *)0)
        return;
    if (arg == (void *)0)
        return;
    root = dspPartner->models[0];
    if (root == 0)
        return;
    if (dspPartnerMsgF != 0)
        dspPartnerMsgF--;
    if (dspPartnerMsgTm != 0)
        dspPartnerMsgTm--;
    else
        dspPartnerMsg = -1;
    if (dspPartnerMsg >= 8)
        dspPartnerMsg = -1;
    for (i = 0; i < 8; i++) {
        {
            GetChild_first = 0;
            HiddenParts(GetChild(root, GetChild_first, 0, i < 4 ? 0 : 1, i & 3, -1), dspPartnerMsgB != i);
        }
    }
    GetChild(root, 0, -1, 0, 0, -1);
    switch (dspPartnerMsgA) {
    case 0:
        if (dspPartnerMsg != dspPartnerMsgB) {
            if (dspPartnerMsg != -1) {
                SetAnimArc2(dspPartner, 0, dspPartnerMsg < 4 ? 1 : 4);
                dspPartnerMsgB = dspPartnerMsg;
                dspPartnerMsgA = 1;
            } else {
                dspPartnerMsgB = -1;
            }
        }
        break;
    case 2:
        if (dspPartnerMsg != dspPartnerMsgB) {
            SetAnimArc2(dspPartner, 0, dspPartnerMsgB < 4 ? 3 : 6);
            dspPartnerMsgA = 3;
        }
        break;
    }
    anim = -1;
    if (jobjAnim(root) != 0) {
        switch (dspPartnerMsgA) {
        case 1:
            if (dspPartnerMsgV != -1 && dspPartnerMsgM != -1) {
                zdVoiceScG(&Zoid[2], dspPartnerMsgV);
            }
            if (dspPartnerMsgB < 4)
                anim = 2;
            else
                anim = 5;
            dspPartnerMsgA = 2;
            break;
        case 3:
            dspPartnerMsgA = 0;
            anim = 0;
            break;
        }
        if (anim != -1) {
            SetAnimArc2(dspPartner, 0, anim);
            jobjAnim(root);
        }
    }
    if ((bar = GetChild(root, 0, 1, 0, -1, -1)) != 0) {
        if (partner->max_health <= 0)
            partner->max_health = 100;
        max = (f32)partner->max_health;
        ratio = (f32)partner->health / max;
        HSD_JObjSetScaleX(bar, ratio);
    }
}
