extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"
#include "zoid3.h"

#include "model_archive.h"
extern void jobjUnrefAll(HSD_JObj *joint);
extern void sDispPurgePartsWarn(void);
extern void sDispPurgePartsPause(void);
extern void sDispPurgePartsOrder(void);
extern void LoadArcAnimModel2(ModelArchive *archive, HSD_JObj *joint, s32 model, s32 selected);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
typedef struct CameraState3 {
    s32 mode;
    s32 half;
    u8 reserved_008[0x1BC];
    ZoidState *zoid;
} CameraState3;
extern s32 pause;
extern s32 sCamNN, sCamNS;
extern s32 gameEndF;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40
#pragma auto_inline off
static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    jobj ? (void)0 : __assert("jobj.h", 605, "jobj");
    return !(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY);
}
#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != 0 && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)
static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    jobj ? (void)0 : __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}
typedef struct GameModeState3 {
    u8 reserved_00[4];
    s32 game_type;
    u8 reserved_08[8];
    s32 win;
    s32 slot;
} GameModeState3;
extern GameModeState3 GameMode;
extern s32 usbForce;
extern s32 nowStage;
extern s32 sprintf(char *buffer, const char *format, ...);
extern ModelArchive *LoadArc2_(char *name, s32 flag);
extern HSD_JObj *CopyJoint2(ModelArchive *archive, s32 model);
extern void PSMTXTrans(f32 *m, f32 x, f32 y, f32 z);
extern void sDispLoadPartsOrder(void);
extern void sDispLoadPartsWarn(void);
extern void sDispLoadPartsPause(void);
extern s32 winF;
extern s32 bp4pNm[];
extern u8 sCamera[];
extern s32 HSD_Randi(s32 range);
extern s32 getEndF(HSD_JObj *joint);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void jobjDisp(HSD_JObj *joint);
extern void sDispLoadPartsMessage(void);
extern ModelArchive *dsp1p;
extern ModelArchive *dspFilter;
extern s32 dspPartnerMsg;
extern s32 dspPartnerMsgF;
extern s32 dspPartnerMsgTm2;
extern s32 gameContinueTm;

void sDispLoadParts(s32 mode, s32 flag);
void sDispPurgePartsGame(void);
void s1pEX(CameraState3 *camera, ZoidState *zoid, HSD_JObj *joint);
void sDispGameFilter(s32 index, s32 mode);
void sDispMessageMe(CameraState3 *camera);
void sDispContinue(void *enable);
#pragma force_active on
static HSD_JObj *dspJobjEx3[4];
static u32 dspAnmEx3[4];
static s32 dspAnmEx3n[4];
static f32 dspMtx[12];
static s32 anmFilter[5];
static s32 onTime;
static ModelArchive *dspSearch;
static ModelArchive *dspScope;
static s32 dspOrder;
static ModelArchive *dspMessage;
static s32 dspWarn;
s32 dspBP;
static s32 dspPause;
static ModelArchive *dspContinue;
static ModelArchive *dspDemoPress;
static ModelArchive *dspRader;
static ModelArchive *dspPartner;
static s32 dspPartnerMsgV;
static s32 dspPartnerMsgM;
static s32 dspPartnerMsgB;
static s32 dspPartnerMsgA;
static ModelArchive *dspPoint;
static ModelArchive *dspPos00;
static s32 menuRet;
#pragma force_active off
static const char lit_374[15] = "disp/order.dat";
static const char lit_381[21] = "disp/div/message.dat";
static const char lit_387[22] = "disp/div/continue.dat";
static const char lit_393[21] = "disp/div/warning.dat";
static const char lit_397[16] = "disp/div/bp.dat";
static const char lit_401[19] = "disp/div/pause.dat";
void sDispLoadParts(s32 mode, s32 flag)
{
    char radar[104];
    char partner[256];
    s32 i;

    dspRader = 0;
    dsp1p = 0;
    onTime = 0;
    dspPos00 = 0;
    dspJobjEx3[0] = 0;
    dspJobjEx3[1] = 0;
    dspJobjEx3[2] = 0;
    dspJobjEx3[3] = 0;
    anmFilter[0] = -1;
    anmFilter[1] = -1;
    anmFilter[2] = -1;
    anmFilter[3] = -1;
    anmFilter[4] = -1;
    dspPartnerMsg = -1;
    dspPartnerMsgV = -1;
    dspPartnerMsgM = -1;
    dspPartnerMsgB = -1;
    dspPartnerMsgA = 0;
    dspPartnerMsgF = 0;
    dspPartnerMsgTm2 = 0;
    if (usbForce != 0)
        flag = 1;
    if (mode == 1 && Zoid[2].joint != 0 && Zoid[0].slot == Zoid[2].slot) {
        sprintf(partner, "chara/bp/bp%03d.dat", Zoid[2].person);
        dspPartner = LoadArc2_(partner, flag);
        SetAnimArc2(dspPartner, 0, 0);
        sDispLoadPartsOrder();
    }
    dspPos00 = LoadArc2_("disp/position00.dat", flag);
    if (sCamNN == 1)
        dspScope = LoadArc2_("disp/scope.dat", flag);
    if (sCamNN == 2) {
        if (sCamNS == 0)
            dspScope = LoadArc2_("disp/scope_01.dat", flag);
        else
            dspScope = LoadArc2_("disp/scope_02.dat", flag);
    }
    dspPoint = LoadArc2_("disp/point.dat", flag);
    if (dspPos00 != 0) {
        dsp1p = LoadArc2_("disp/interface.dat", flag);
        onTime = 0;
    }
    sprintf(radar, "disp/radar%02d.dat", nowStage);
    dspRader = LoadArc2_(radar, flag);
    dspSearch = LoadArc2_("disp/search.dat", flag);
    dspAnmEx3[0] = 3;
    dspAnmEx3n[0] = -1;
    dspAnmEx3n[1] = -1;
    dspAnmEx3n[2] = -1;
    dspAnmEx3n[3] = -1;
    if (sCamNN != 4) {
        dspJobjEx3[0] = CopyJoint2(dsp1p, 3);
        if (sCamNN == 2 && sCamNS == 1)
            dspAnmEx3[1] = 4;
        else
            dspAnmEx3[1] = 3;
        dspAnmEx3[2] = 3;
        dspAnmEx3[3] = 3;
        dspJobjEx3[1] = CopyJoint2(dsp1p, dspAnmEx3[1]);
        dspJobjEx3[2] = CopyJoint2(dsp1p, dspAnmEx3[2]);
        dspJobjEx3[3] = CopyJoint2(dsp1p, dspAnmEx3[3]);
    } else {
        for (i = 0; i < 4; i++) {
            dspAnmEx3[i] = 20;
            dspJobjEx3[i] = CopyJoint2(dsp1p, dspAnmEx3[i]);
        }
    }
    menuRet = 0;
    PSMTXTrans(dspMtx, 0.0f, 0.0f, 0.0f);
    sDispLoadPartsWarn();
    sDispLoadPartsPause();
    if (GameMode.game_type == 9 && dspDemoPress == 0)
        dspDemoPress = LoadArc2("disp/demo_press.dat");
}

void sDispPurgePartsGame(void)
{
    static char str[256];
    if (dspJobjEx3[0] != 0)
        jobjUnrefAll(dspJobjEx3[0]);
    if (dspJobjEx3[1] != 0)
        jobjUnrefAll(dspJobjEx3[1]);
    if (dspJobjEx3[3] != 0)
        jobjUnrefAll(dspJobjEx3[2]);
    if (dspAnmEx3[0] != 0)
        jobjUnrefAll(dspJobjEx3[3]);
    dspJobjEx3[0] = 0;
    dspJobjEx3[1] = 0;
    dspJobjEx3[2] = 0;
    dspJobjEx3[3] = 0;
    if (dspSearch != 0)
        PurgeArc2(dspSearch);
    dspSearch = 0;
    if (dspRader != 0)
        PurgeArc2(dspRader);
    dspRader = 0;
    if (dsp1p != 0)
        PurgeArc2(dsp1p);
    dsp1p = 0;
    if (dspPartner != 0)
        PurgeArc2(dspPartner);
    dspPartner = 0;
    if (dspPoint != 0)
        PurgeArc2(dspPoint);
    dspPoint = 0;
    if (dspScope != 0)
        PurgeArc2(dspScope);
    dspScope = 0;
    sDispPurgePartsWarn();
    sDispPurgePartsPause();
    sDispPurgePartsOrder();
}

#pragma force_active on
HSD_JObj *jobjFilter[5];
s32 dspFileA[16];
s32 dspFileGrid[16];
#pragma force_active off
#pragma dont_inline off
void s1pEX(CameraState3 *camera, ZoidState *zoid, HSD_JObj *joint)
{
    HSD_JObj *child;
    HSD_JObj *gauge;
    HSD_JObj *bar;
    s32 state;
    f32 ratio;

    if (joint != 0 && zoid != (void *)0 && zoid->joint != (void *)0 && zoid->super_attack_enabled != 0) {
        child = GetChild(joint, 0, 2, -1, -1, -1);
        if (child != 0) {
            gauge = dspJobjEx3[camera->half];
            if (gauge != (void *)0) {
                jobjCopyPos(child, gauge);
                state = 0;
                ratio = (600.0f - (f32)zoid->super_attack_cooldown) / 600.0f;
                bar = GetChild(gauge, 0, 1, -1, -1, -1);
                HSD_JObjSetScaleX(bar, ratio);
                if (zoid->super_attack_cooldown != 0)
                    state = 1;
                if (state != dspAnmEx3n[camera->half]) {
                    LoadArcAnimModel2(dsp1p, gauge, dspAnmEx3[camera->half], state);
                    dspAnmEx3n[camera->half] = state;
                }
                if (pause == 0)
                    jobjAnim(gauge);
                jobjDispAll(gauge);
            }
        }
    }
}
#pragma dont_inline on

void sDispGameFilter(s32 index, s32 mode)
{
    s32 next;

    if (index < 0)
        return;
    if (index > 4)
        return;
    if (jobjFilter[index] == (void *)0)
        return;
    if (dspFilter == 0)
        return;
    if (anmFilter[index] == -1) {
        if (mode == 0)
            return;
        if (mode == 1)
            next = 0;
        else
            next = 3;
        LoadArcAnimModel2(dspFilter, jobjFilter[index], 0, next);
        anmFilter[index] = next;
        return;
    }
    if (jobjAnim(jobjFilter[index]) != 0) {
        next = anmFilter[index];
        switch (next) {
        case 0:
            next = 1;
            break;
        case 1:
            if (mode != 1)
                next = 2;
            break;
        case 2:
            next = -1;
            break;
        case 3:
            next = 4;
            break;
        case 4:
            if (mode != 2)
                next = 5;
            break;
        case 5:
            next = -1;
            break;
        default:
            return;
        }
        if (next != anmFilter[index]) {
            if (next != -1) {
                LoadArcAnimModel2(dspFilter, jobjFilter[index], 0, next);
                jobjAnim(jobjFilter[index]);
            }
            anmFilter[index] = next;
        }
        if (next == -1)
            return;
    }
    jobjDispAll(jobjFilter[index]);
}

static const char lit_647[37] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static const u32 lit_1430[5] = { 0xFFFFFFFF, 0x00000000, 0x00000003, 0x00000001, 0x00000002 };
static const u32 lit_1461[5] = { 0xFFFFFFFF, 0x00000000, 0x00000003, 0x00000001, 0x00000002 };
void sDispMessageMe(CameraState3 *camera)
{
    s32 tblA[4] = { 2, 0, 2, 1 };
    s32 tblB[4] = { 8, 7, 8, 8 };
    s32 tblC[4] = { 2, 3, 2, 4 };
    HSD_JObj *joint;
    HSD_JObj *target;
    HSD_JObj *child;
    s32 pick;
    s32 value;
    ZoidState *zoid;
    static s8 bJa;

    zoid = camera->zoid;
    if (gameEndF >= 4) {
        if (gameEndF == 4)
            sDispLoadPartsMessage();
        if (dspMessage != 0) {
            joint = dspMessage->models[5];
            if (joint != (void *)0) {
                if (gameEndF <= 11) {
                    target = 0;
                    if (dspPos00 != 0) {
                        if (sCamNN == 2)
                            target = GetChild(dspPos00->models[sCamNS + 1], 0, camera->half, 10, -1, -1);
                        if (sCamNN == 4)
                            target = GetChild(dspPos00->models[3], 0, camera->half, 10, -1, -1);
                    }
                    if (target != 0)
                        jobjCopyPos(target, joint);
                    if (camera == (CameraState3 *)sCamera)
                        jobjAnim(joint);
                    if (gameEndF == 4) {
                        bJa = 0;
                        return;
                    }
                    if (winF != 0) {
                        switch (bJa) {
                        case 0:
                            Zoid[0].rumble_timer = 0;
                            Zoid[1].rumble_timer = 0;
                            Zoid[2].rumble_timer = 0;
                            Zoid[3].rumble_timer = 0;
                            if (GameMode.game_type == 1 && camera->zoid == 0 && winF == 1) {
                                value = HSD_Randi(4) + 7;
                                if (value < 7)
                                    value = 7;
                                if (value > 10) {
                                    (void)0;
                                }
                            }
                            SetAnimArc2(dspMessage, 5, 0);
                            bJa = 1;
                            return;
                        case 1:
                            if (getEndF(joint) != 0) {
                                SetAnimArc2(dspMessage, 5, 1);
                                bJa = 2;
                            }
                            break;
                        case 2:
                            if (gameEndF == 6)
                                bJa = 3;
                            else
                                getEndF(joint);
                            break;
                        case 3:
                            SetAnimArc2(dspMessage, 5, 2);
                            bJa = 4;
                            break;
                        case 4:
                            if (getEndF(joint) != 0) {
                                SetAnimArc2(dspMessage, 5, 3);
                                bJa = 5;
                                return;
                            }
                            break;
                        case 5:
                            return;
                        }
                        pick = tblA[winF];
                        if (sCamNN == 2) {
                            if (pick == 0) {
                                if (camera->half == 0)
                                    pick = 3;
                                else
                                    pick = 4;
                            }
                            if (pick == 1) {
                                if (camera->half == 0)
                                    pick = 4;
                                else
                                    pick = 3;
                            }
                        }
                        if (GameMode.game_type == 4)
                            pick = tblB[winF];
                        if (GameMode.game_type == 5) {
                            if (GameMode.slot == -1) {
                                pick = tblC[2];
                                if (bp4pNm[zoid->slot] != 1)
                                    pick = tblC[3];
                            } else if (zoid != 0 && GameMode.slot == zoid->slot) {
                                pick = tblC[1];
                            } else {
                                pick = tblC[3];
                            }
                        }
                        if (pick != -1) {
                            child = GetChild(joint, 0, 9, -1, -1, -1);
                            HiddenParts(child, 0);
                            jobjDisp(child);
                            child = GetChild(joint, 0, pick, -1, -1, -1);
                            HiddenParts(child, 0);
                            jobjDisp(child);
                        }
                    }
                }
            }
        }
    }
}

void sDispContinue(void *enable)
{
    s32 time;
    HSD_JObj *yes;
    HSD_JObj *count;
    static s32 cont;
    s32 i;
    HSD_JObj *base;
    s32 dead;
    HSD_JObj *no;

    if (gameEndF < 9) {
        cont = 0;
        return;
    }
    if (dspContinue == 0)
        return;
    if (enable == (void *)0)
        return;
    if (gameEndF >= 11)
        return;
    if (GameMode.game_type != 1)
        return;
    base = dspContinue->models[0];
    yes = dspContinue->models[1];
    no = dspContinue->models[2];
    count = dspContinue->models[3];
    if (base == (void *)0)
        return;
    if (yes == (void *)0)
        return;
    if (no == (void *)0)
        return;
    if (count == (void *)0)
        return;
    if (jobjAnim(yes) != 0)
        SetAnimArc2(dspContinue, 1, GameMode.win == 3 ? 2 : 1);
    if (jobjAnim(no) != 0)
        SetAnimArc2(dspContinue, 2, GameMode.win == 0 ? 2 : 1);
    jobjAnim(count);
    switch (cont) {
    case 0:
        SetAnimArc2(dspContinue, 0, 1);
        SetAnimArc2(dspContinue, 3, 1);
        cont = 1;
        break;
    case 1:
        jobjAnim(base);
        if (gameEndF == 10) {
            SetAnimArc2(dspContinue, 0, 2);
            SetAnimArc2(dspContinue, 3, 2);
            cont = 2;
        }
        break;
    case 2:
        if (jobjAnim(base) != 0) {
            gameEndF = 12;
            return;
        }
        break;
    }
    for (i = 0; i < 6; i++) {
        HiddenParts(GetChild(base, 0, i, -1, -1, -1), i != 0);
        dead = 1;
    }
    jobjDispAll(base);
    if (gameContinueTm > 0) {
        jobjDispAll(yes);
        jobjDispAll(no);
    } else if (GameMode.win == 3) {
        jobjDispAll(yes);
    } else {
        jobjDispAll(no);
    }
    time = gameContinueTm / 60;
    if (time >= 0 && time < 10) {
        for (i = 0; i < 10; i++) {
            HiddenParts(GetChild(count, 0, i, -1, -1, -1), time != i);
            dead = 1;
        }
    }
    if (GameMode.win == 3 && gameEndF == 10)
        return;
    jobjDispAll(count);
}

#pragma force_active on
ModelArchive * dspFilter;
s32 dspPartnerMsgF;
s32 dspPartnerMsgTm2;
s32 dspPartnerMsgTm;
s32 dspPartnerMsg;
ModelArchive * dsp1p;
s32 dspOrderAI;
s32 dspOrderTm;
s32 gameTime;
s16 dlgzoidno;
s16 dlgpartsno;
s16 dlgpersonno;
#pragma force_active off
static const char lit_1897[9] = "\x8f\x9f\x97\x98\x8f\xf0\x8c\x8f";
static const u32 lit_1984[6] = { 0x00000000, 0x00000001, 0x00000003, 0x00000004, 0x00000005, 0x00000006 };
static const char lit_2083[14] = "-- cam-- end\n";
}
