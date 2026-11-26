extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"

#include "zoid3.h"
extern void OSReport(const char *fmt, ...);
extern void *OSGetArenaLo(void);
extern void *OSGetArenaHi(void);
extern u32 OSGetPhysicalMemSize(void);
extern s32 OSCreateHeap(void *lo, void *hi);
typedef struct GameMode3 {
    s32 f00;
    s32 game_type;
    s32 f08;
    s32 f0C;
    s32 win;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 map;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
} GameMode3;
extern u8 IveSaveFlag[7344];
extern s32 bitTBL[14];
extern s32 gameTime;
extern s32 suddenDeath(ZoidState *a, ZoidState *b);
typedef struct FixData {
    u32 sum;
    s32 size;
    u8 rest[1];
} FixData;
extern u8 IveSave[66096];
extern void ZeroMemory(void *p, s32 n);
extern void MemCpy(void *d, void *s, s32 n);
extern void camVoiceOn(s32 chara, s32 vc);
extern void zdVoiceSc(ZoidState *z, s32 no);
extern u8 *sPad1;
typedef struct F1 {
    f32 v;
} F1;
typedef struct VIX {
    u8 pad[0x48];
    F1 f48;
} VIX;
extern VIX HSD_VIData;
typedef struct FogG3 { u8 pad[0x18]; F1 color; } FogG3;
extern void debugFileUnPurgeList(void);
extern void ascPrologue(void);
extern void ascEpilogue(void);
extern void *CopyJoint2(void *p, s32 n);
extern void ZoidPrologue(void);
extern void GameZoidInit(void);
extern void sWeaponPrologue(void);
extern void sWeaponEpilogue(void);
extern void zDispCursorPrologue(void);
extern void zDispCursorEpilogue(void);
extern void HSD_StateInvalidate(s32 n);
extern void HSD_FogSet(s32 n);
extern void HSD_SetZSortMode(s32 a, s32 b);
extern void HSD_VISetBlack(s32 n);
extern void ttlMain(void);
extern void loadMapInfo(void);
extern s32 HSD_Randi(s32 n);
extern void *rdMapInfo(s32 a, s32 b);
extern void VIWaitForRetrace(void);
extern void Epilogue(void);
extern void allRank(void);
extern void waitV(s32 n);
extern void resetSkipOp(void);
extern void ZoidEpilogue(void);
extern void jobjUnrefAll(void *p);
extern void sReadPre(void);
extern void chkVS(void);
extern void HSD_AudioStreamStop(s32 n);
extern void HSD_AudioSFXKeyOffAll(void);
extern void TEA_SoundSfxPop(void);
extern void game0(void);
extern void batFlag(void);
extern void *jobjFilter[5];
extern ModelArchive *dspFilter;
extern s32 sCamNN;
extern s32 sCamNN2;
extern FogG3 *fogG;
extern s32 sPadRep;
extern s32 dspLoadF;
extern u8 TeaSoundSfxLoadNum;
typedef struct MgI3 {
    u8 pad0[0x2ad4];
    s32 f2AD4;
    u8 pad1[0x308a - 0x2ad8];
    s16 f308A;
    u8 pad2[0x3092 - 0x308c];
    s8 f3092;
    u8 pad3[0x321c - 0x3093];
    s8 f321C;
} MgI3;
extern MgI3 mgI;
extern MgI3 *mgP;
extern s32 usrHeap;
extern void TeaBgm(s16 no);
extern s32 SeOn(s32 no);
extern s32 calcRank(s32 v);
extern u32 OSGetResetCode(void);
extern void OSSetSaveRegion(s32 lo, s32 hi);
extern void fixSave(void);
extern void init_alloc(s32 n);
extern void init_2(void);
extern void sFileInit(void);
extern void configClear(void);
extern void configGet(void);
extern s32 fixGet(void);
extern void HSD_Init(void);
extern void sPadInit(void);
extern void sPadAll(void);
extern s32 sFontInit(void);
extern void debug11(void);
extern void HSD_PadInit(s32 n, void *q, s32 a, s32 b);
extern void TEA_SoundInit(void);
extern void TEA_SoundDefLoad(void);
extern void TEA_defstatusload(void);
extern void TEA_mcInit(void);
extern u32 OSGetSoundMode(void);
extern void sndOutputMode(s32 n);
extern void sCameraInit(void);
extern void initPtcl(void);
extern void readPtcl(char *name);
extern void forgetPtcl(void);
extern void TEA_AudioSeqStop(void);
extern void TEA_AudioSeqFree(void);
extern void HSD_GetVersion(s32 *a, s32 *b, s32 *c, s32 *d);
extern u8 GXNtsc480IntDf[0x3c];
extern ModelArchive *menu_saveloadiconp;
extern ModelArchive *menu_yesnop;
extern void mainLoop(void);
extern s32 HSD_SetInitParameter(s32 id, ...);
extern void *memcpy(void *d, const void *s, u32 n);
#include "os_time.h"
typedef struct RM3 {
    u8 b[0x3c];
} RM3;
typedef struct Cam3 {
    u8 pad0[8];
    void *lights;
    u8 pad1[0x1c4 - 0xc];
    ZoidState *zoid;
    u8 pad2[0x1f0 - 0x1c8];
    f32 v1f0[3];
    u8 pad3[0x208 - 0x1fc];
    f32 v208[3];
    f32 v214[3];
    u8 pad4[0x244 - 0x220];
    void *cobj;
    u8 pad5[0x2f9 - 0x248];
    s8 f2F9;
    s8 f2FA;
    s8 f2FB;
    u8 pad6[0x590 - 0x2fc];
} Cam3;
extern Cam3 sCamera[4];
extern Cam3 *camTmp;
extern s32 offShadow;
extern void dummyFunc(char *s);
extern void sCameraCtrl(Cam3 *c);
extern void ZoidAI(void);
extern void camOnStart(Cam3 *c);
extern void sCameraON(Cam3 *c);
extern void camOnWin(Cam3 *c);
extern void camOnDie(Cam3 *c);
extern void camOnScope(Cam3 *c);
extern void gameStartZoid(void);
extern s32 isMsgHelp(void);
extern void clearMsgHelpPage(void);
extern s32 isMsgHelpPage(s32 p);
extern void purgeMsgHelp(void);
extern void ZoidLen(void);
extern void ZoidAllAnim(void);
extern void ZoidAllMat(void);
extern void ZoidAllMove(void);
extern void grdObjAnim(void);
extern void grdObjTest(void);
extern void sMissileMove(void);
extern void psInterpretParticles(s32 n);
extern void psExecGenerator(s32 n);
extern void ZoidSearchTop(void);
extern void ZoidAllPutXZ(void);
extern void sWeaponAnimAll(void);
extern void ZoidWeaponActLoop(void);
extern void sLsrMove(void);
extern void ZoidZdCoObjBodyAll(void);
extern void ZoidCoObjAll(void);
extern void ZoidZdAll(void);
extern void sWeaponMoveAll(void);
extern void sEffectAnimAll(void);
extern void ZoidAllSmoke(void);
extern void sCameraShadowAll(void);
extern void sDispAnim(void);
extern s32 gameEnd(void);

typedef struct C4 { u8 r, g, b, a; } C4;
typedef struct Ctl3 { u8 pad[0x140]; s32 w[16]; } Ctl3;
typedef struct SkyS { u8 pad[0x30]; void *lights; } SkyS;
extern SkyS *Sky;
extern s32 VsMode;
extern s32 VsTime;
extern s32 VsTimeTBL[8];
extern s32 sCamNS2;
extern s32 vsyncN;
extern u8 *sPad2;
extern u8 *sPad3;
extern u8 *sPad4;
extern u8 sPad[4][0x88];
extern s16 TEA_SEVOL;
extern void sMissileEpilogue(void);
extern void sEffectEpilogue(void);
extern s32 HSD_Rand(void);
extern s32 sprintf(char *s, const char *fmt, ...);
extern s32 fexistU(char *path, s32 mode);
extern void putErr(char *s);
extern void LoadStageNow(s32 n);
extern void ZoidInitAll(void);
extern void ZoidCalcAll(void);
extern void ZoidVoiceScript(void);
extern void zdSearchPosPoly(ZoidState *z);
extern void zdOnGround(ZoidState *z);
extern void zdCoStartPos(ZoidState *z);
extern void zdWeaponChg(ZoidState *z);
extern void ZoidAmbientSetSkyAll(void);
extern void aiPrologue(s32 n);
extern void aiEpilogue(s32 n);
extern void sCameraPurge(void);
extern void sCameraSetQuat(Cam3 *c, s32 n);
extern s32 ZoidInit(ZoidState *z, s32 id);
extern void sCameraTargetZoid(Cam3 *c, ZoidState *z);
extern void sDispLoadParts(s32 a, s32 b);
extern void sCameraSetHalf2(Cam3 *c, s32 n);
extern void sCameraSetHalf(Cam3 *c, s32 n);
extern void sCameraSetNormal(Cam3 *c);
extern void sCameraSetShadowAll(void);
extern void ZoidSetAnim(ZoidState *z, s32 n);
extern void sEffectPrologue(void);
extern void sMissilePrologue(void);
extern void sLsrPrologue(void);
extern void sLsrEpilogue(void);
extern void IntSePrologue(void);
extern void IntSeClear(void);
extern void IntSeClose(void);
extern u32 VIGetRetraceCount(void);
extern void vcStart(void);
extern s32 vcEnd(char *s);
extern s32 gameWin(void);
extern void motWinSet(void);
extern s32 HSD_GetHeap(void);
extern void *OSAllocFromHeap(s32 heap, u32 size);
extern void OSFreeToHeap(s32 heap, void *p);
extern void HSD_Free(void *p);
extern void drawAll(void);
extern void sPutFontAllNn(void);
extern void HSD_VICopyXFB(s32 n);
extern void HSD_VISetXFBDrawDone(void);
extern void sDispPauseProc(void);
extern void setBpTBL(void);
extern s32 putBP(void);
extern void TEA_VoiceOn(s32 a, s32 b);
extern s32 TEA_SeKeyOn(u16 id, u8 vol, u8 a, u32 b);
extern void sMissilePurgeAll(void);
extern void sDispPurgeParts(void);
extern void sWeaponUnMountAll(ZoidState *z);
extern void ZoidPurgeAll(void);
extern void PurgeStageData(void);
extern void psKillAllGenerator(void);
extern void psKillAllParticle(void);
extern s32 gClear(void);

s32 calcEndVsMan(void);
s32 sortEndVs4p(void);
void game1(void);
s32 putBP(void);
void voiceSet(s32 who);
void setBpTBL(void);
void game0(void);
s32 fixGet(void);
#pragma force_active on
static s32 aram_block[16];
GameMode3 GameMode;
s32 bp4pNm[10];
static s32 vNowTBL[80];
s32 bp[12];
static const char lit_371[15] = "tex/1_B_KA.DTX";
static const char lit_534[14] = "grp=%d nm=%d\n";
static const char lit_535[16] = "No.1 grp N =%d\n";
static const char lit_870[12] = " CamRumble ";
static const char lit_881[9] = ">mode3 \n";
static const char lit_884[11] = "ZAllMove,\n";
static const char lit_891[9] = "ZCBody,\n";
static const char lit_1099[21] = "chara =%d , vc =%d \n";
ModelArchive *dspLoad;
s32 normLineDEBUG;
s32 ctrlZoid;
static s32 AreaIn;
static s32 AreaIn2;
static s32 sPage;
static s32 vNow;
static s32 vNowO;
s32 drawTime;
s32 drawTimeG;
static s32 vOn44;
static FixData *fix;
static s32 lastGame;
u32 usrLO;
s32 gametime;
typedef struct BpTm2 { s32 a; s32 b; } BpTm2;
BpTm2 bpTm;
s32 pause;
s32 gameContinueTm;
s32 gameEndTm;
s32 gameEndF;
s32 gameStartTm;
s32 gameStartF;
s32 winF;
s32 grdcH2TBL;
s32 grdcD2TBL;
s32 grdcPolygon;
s32 grdcMat;
s32 grdcNormal;
s32 grdcVtx;
s32 grdcEndZ;
s32 grdcEndX;
s32 grdcDiffZ;
s32 grdcDiffX;
s32 grdcStartZ;
s32 grdcStartX;
s32 grdcDivZ;
s32 grdcDivX;
s32 grdcNn;
s32 grdcMn;
s32 grdcVn;
s32 grdcPn;
s32 grdcCol;
#pragma force_active off
s32 calcEndVsMan(void)
{
    s32 flags = 0;
    ZoidState *z0 = &Zoid[0];
    ZoidState *z1 = &Zoid[1];
    if (GameMode.f3C == -1) {
        if (z0->death_started == 0 && z0->field_1E7C != 0) {
            flags |= 1;
        }
        if (z1->death_started == 0 && z1->field_1E7C != 0) {
            flags |= 2;
        }
        if (flags != 0) {
            if (flags & 1) {
                GameMode.f3C = 0;
            }
            if (flags & 2) {
                GameMode.f3C = 1;
            }
            if (flags == 3) {
                GameMode.f3C = 99;
            }
        }
    }
    if (GameMode.f3C != -1) {
        if (GameMode.f3C == 0) {
            return 1;
        }
        if (GameMode.f3C == 1) {
            return 3;
        }
        return 2;
    }
    if (z0->death_started == 0) {
        if (z1->death_started != 0) {
            return 1;
        }
    } else {
        if (z1->death_started == 0) {
            return 3;
        }
        return 2;
    }
    return suddenDeath(z0, z1);
}

s32 sortEndVs4p(void)
{
    s32 cnt[10];
    s32 total[10];
    s32 ave[10];
    s32 hp2[10];
    s32 alive[10];
    s32 i;
    s32 j;
    s32 k;
    ZoidState *z;
    for (i = 0; i < 10; i++) {
        cnt[i] = 0;
        total[i] = 0;
        hp2[i] = 0;
        alive[i] = 0;
        bp4pNm[i] = 1;
        ave[i] = 0;
    }
    for (k = 0; k < 16; k++) {
        z = &Zoid[k];
        if (z->joint != 0) {
            i = z->slot;
            cnt[i]++;
            total[i] += z->health;
            hp2[i] += z->field_20F8;
            if (z->death_started == 0) {
                alive[i]++;
            }
        }
    }
    for (i = 0; i < 10; i++) {
        ave[i] = 0;
        if (cnt[i] != 0) {
            ave[i] = total[i] / cnt[i];
        }
    }
    for (k = 0; k < 16; k++) {
        for (i = 0; i < 10; i++) {
            if (cnt[i] != 0) {
                for (j = 0; j < 10; j++) {
                    if (cnt[j] != 0 && i != j && bp4pNm[i] == bp4pNm[j]) {
                        if (ave[i] > ave[j]) {
                            bp4pNm[j]++;
                        } else if (ave[i] < ave[j]) {
                            bp4pNm[i]++;
                        }
                    }
                }
            }
        }
    }
    i = 0;
    j = 0;
    for (; i < 10; i++) {
        if (cnt[i] != 0) {
            if (bp4pNm[i] == 1) {
                j++;
            }
            OSReport(lit_534, i, bp4pNm[i]);
        } else {
            bp4pNm[i] = 0;
        }
    }
    OSReport(lit_535, j);
    return j;
}

void game1(void)
{
    s32 i;
    ZoidState *z;
    s64 t;
    t = OSGetTime();
    dummyFunc(lit_870);
    camTmp = sCamera;
    if (gameEndF >= 4) {
        for (i = 0; i < 16; i++) {
            z = &Zoid[i];
            if (z->joint != (void *)0) {
                z->rumble_timer = 0;
            }
        }
    }
    dummyFunc("ZoidAI ");
    if (gameEndF <= 3 && gameStartF == 0) {
        for (i = 0; i < 4; i++) {
            dummyFunc("Cc:");
            sCameraCtrl(&sCamera[i]);
        }
        dummyFunc("Zz:");
        ZoidAI();
    }
    dummyFunc("Scope ");
    if (gameEndF <= 5) {
        for (i = 0; i < 4; i++) {
            dummyFunc("/");
            camTmp = &sCamera[i];
            if (gameStartF != 0) {
                dummyFunc("a");
                if (gameStartF == 1) {
                    camOnStart(camTmp);
                }
                if (gameStartF == 2) {
                    sCameraON(camTmp);
                }
            } else if (camTmp->f2F9) {
                dummyFunc("b");
                camOnWin(camTmp);
            } else if (camTmp->f2FA) {
                dummyFunc("c");
                camOnDie(camTmp);
            } else if (camTmp->f2FB) {
                dummyFunc("d");
                camOnScope(camTmp);
            } else {
                dummyFunc("f");
                sCameraON(camTmp);
            }
        }
    }
    dummyFunc(lit_881);
    if (gameEndF <= 3) {
        switch (gameStartF) {
        case 0:
            break;
        case 1:
            gameStartTm++;
            if (gameStartTm == 0x3c) {
                zdVoiceSc(Zoid, 2);
            }
            if (gameStartTm > 0x12c) {
                gameStartZoid();
                if (isMsgHelp() != 0) {
                    gameStartF = 2;
                    sPage = 0;
                    clearMsgHelpPage();
                }
            }
            break;
        case 2:
            if (isMsgHelpPage(sPage) != 0) {
                if (*(s8 *)(sPad1 + 0x5d) != 0) {
                    sPage++;
                }
                if (*(s8 *)(sPad1 + 0x5e) != 0 && sPage != 0) {
                    sPage--;
                }
                *(s8 *)(sPad1 + 0x5d) = 0;
            } else if (*(s8 *)(sPad1 + 0x42) == 0) {
                purgeMsgHelp();
                gameStartZoid();
            }
            break;
        }
        if (offShadow != 0) {
            offShadow--;
        }
        camTmp = sCamera;
        dummyFunc("ZLen,\n");
        ZoidLen();
        dummyFunc("ZAAn,\n");
        ZoidAllAnim();
        ZoidAllMat();
        dummyFunc(lit_884);
        if (gameStartF != 2) {
            ZoidAllMove();
        }
        dummyFunc("GrdA,\n");
        grdObjAnim();
        grdObjTest();
        dummyFunc("Mis,\n");
        sMissileMove();
        psInterpretParticles(0);
        psExecGenerator(0);
        dummyFunc("ZTop,\n");
        ZoidSearchTop();
        dummyFunc("Zpr,\n");
        if (gameStartF != 2) {
            ZoidAllPutXZ();
        }
        dummyFunc("ZAmat,\n");
        ZoidAllMat();
        sWeaponAnimAll();
        dummyFunc("ZWAct,\n");
        ZoidWeaponActLoop();
        sLsrMove();
        dummyFunc(lit_891);
        ZoidZdCoObjBodyAll();
        dummyFunc("ZCobj,\n");
        ZoidCoObjAll();
        dummyFunc("Zzal,\n");
        ZoidZdAll();
        dummyFunc("WMove,\n");
        sWeaponMoveAll();
        dummyFunc("EAnim,\n");
        sEffectAnimAll();
        ZoidAllSmoke();
        dummyFunc("Sha,\n");
        sCameraShadowAll();
        sDispAnim();
        if (gameEnd() != 0 && gameEndF == 0) {
            gameEndF = 1;
        }
        if (gameEndF != 0) {
            if ((u32)gameEndTm == 1) {
                if (GameMode.game_type == 1 || GameMode.game_type == 2 || GameMode.game_type == 3 || GameMode.game_type == 5) {
                    SeOn(0x74);
                }
            }
            gameEndTm++;
            if ((u32)gameEndTm > 0xb4) {
                if (gameEndF == 1) {
                    gameEndF = 2;
                    TeaBgm(-1);
                }
            } else if (Zoid[0].field_1E74 != 0) {
                gameEndTm = 0x12c;
            }
        } else {
            gameEndTm = 0;
        }
        drawTimeG = OSGetTime() - t;
    }
    (void)lit_870;
}

s32 putBP(void)
{
    s32 calcRank_v;

    ZoidState *z2;
    s32 fin;
    s32 cnt;
    s32 i;
    s32 j;
    s32 s1;
    ZoidState *z0;
    s32 s2;
    s32 rank;
    z0 = Zoid;
    z2 = &Zoid[2];
    if (z2->joint == 0) {
        z2 = 0;
    }
    if (z2 != 0 && z2->max_health == 0) {
        z2 = 0;
    }
    fin = 0;
    if (GameMode.game_type == 4) {
        fin = 1;
    }
    if (bpTm.a == 0) {
        return 0;
    }
    if (bpTm.a < 0x3c) {
        bpTm.a = bpTm.a + 1;
        GameMode.f40 = 0;
        bpTm.b = 0;
    } else {
        i = 0;
        cnt = 0;
        for (; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if ((bp + 6)[i] < bp[i]) {
                    (bp + 6)[i]++;
                    if (*(s8 *)(sPad1 + 0x42) != 0 || fin != 0) {
                        (bp + 6)[i] = bp[i];
                    }
                    cnt++;
                }
            }
        }
        if (cnt == 0) {
            fin = 1;
        }
    }
    if (fin != 0) {
        bpTm.b++;
        if (bpTm.b > 0x3c && GameMode.f40 == 0) {
            if (z0->max_health <= 0) {
                s1 = 100;
            } else {
                s1 = z0->health * 100 / z0->max_health;
            }
            if (z2 != 0) {
                s2 = z2->health * 100 / z2->max_health;
            } else {
                s2 = s1;
            }
            {
                calcRank_v = (s32)((s1 + s2) / 2.0);
                rank = calcRank(calcRank_v);
            }
            GameMode.f40 = rank;
            if (GameMode.f40 != 0) {
                SeOn(0x57);
            }
        }
        if (bpTm.b > 0x12c) {
            return 1;
        }
    }
    return 0;
}

void voiceSet(s32 who)
{
    s32 vc;
    s32 i;
    ZoidState *z;
    if (vOn44 == 0) {
        if (GameMode.game_type == 4) {
            TeaBgm(who == 1 ? 9 : 10);
            if ((s32)IveSave[0x1c8e] == 1) {
                i = 0x4b;
            } else {
                i = 0x4b;
            }
            if (who <= 1) {
                vc = 1;
            } else {
                vc = 2;
            }
            camVoiceOn(i, vc);
            OSReport(lit_1099, i, vc);
        }
        if (GameMode.game_type == 1 || GameMode.game_type == 3) {
            TeaBgm(who == 1 ? 9 : 10);
            if (who == 1) {
                zdVoiceSc(&Zoid[0], 7);
            } else {
                for (i = 1; i < 16; i++) {
                    z = &Zoid[i];
                    if (z->joint == 0 || (u8)z->slot == Zoid[0].slot) {
                        continue;
                    }
                    break;
                }
                if (i != 16) {
                    zdVoiceSc(&Zoid[i], 7);
                }
            }
        }
        if (GameMode.game_type == 2) {
            TeaBgm(9);
            zdVoiceSc(&Zoid[who == 1 ? 0 : 1], 7);
        }
        if (GameMode.game_type == 5) {
            TeaBgm(9);
        }
        vOn44 = 1;
    }
}

void setBpTBL(void)
{
    s32 i;
    if (GameMode.game_type == 1 || GameMode.game_type == 4) {
        GameMode.win = 2;
        for (i = 0; i < 6; i++) {
            bp[i] = 0;
            (bp + 6)[i] = 0;
        }
        if (gameTime > 0) {
            bp[0] = gameTime / 60 * 10;
        }
        if (bp[0] > 9999) {
            bp[0] = 9999;
        }
        bp[1] = Zoid[0].health;
        if (Zoid[2].joint) {
            bp[2] = Zoid[2].health;
        } else {
            bp[2] = Zoid[0].max_health / 2;
        }
        bp[3] = Zoid[0].field_1EF0;
        bp[4] = Zoid[0].field_1EF4;
        bp[5] = 0;
    }
}

#pragma dont_inline off
static inline void setClear(F1 color)
{
    HSD_VIData.f48 = color;
}
static inline void clearBlack(void)
{
    F1 z = {0.0f};
    setClear(z);
}
void game0(void)
{
    s32 i;
    ZoidState *z;
    s32 k;
    s32 t;
    s32 j;
    Cam3 *cam;
    ZoidState *cz;
    s32 idx;
    s32 cnt;
    u32 tick;
    u32 now;
    s32 draw;
    s32 npads;
    s32 c;
    s32 b;
    s32 a;
    u32 last;
    s32 stage;
    s32 bpcnt;
    s32 skip;
    s32 prevbp;
    s32 cnt5;
    char path[80];
    s32 ok;
    Ctl3 *ctrl;
    ZoidState *zoid;
    s32 f;
    Ctl3 *ctrl2;
    s32 vt;
    s32 d84;
    s32 d80;
    static char str[50];
    static s32 bak[1] = {-1};

    skip = 0;
    a = 3;
    b = 2;
    c = 2;
    a = 2;
    b = 1;
    c = 1;
    a = 3;
    b = 1;
    c = 1;
    if (GameMode.game_type == 5) {
        a = 4; c = 1; b = 1;
    }
    if (GameMode.game_type == 9) {
        a = 3;
    }
    gameEndTm = 0;
    gameEndF = 0;
    GameMode.f14 = -1;
    sMissileEpilogue();
    sEffectEpilogue();
    OSReport("#\203Q\201[\203\200\203X\203^\201[\203g!! GameMode.type=%d\n", GameMode.game_type);
    vOn44 = 0;
    stage = HSD_Rand() % 17 + 1;
    if (GameMode.game_type == 1) {
        stage = mgI.f2AD4;
        GameMode.f28 = stage;
    }
    if (GameMode.game_type == 4) {
        stage = mgI.f2AD4;
        GameMode.f28 = stage;
    }
    stage = mgI.f2AD4;
    GameMode.f28 = stage;
    stage = GameMode.f28;
    ok = 1;
    sprintf(path, "stage/st%02d.dat", stage);
    if (fexistU(path, 0) == 0) {
        ok = 0;
    }
    sprintf(path, "stage/skymap%02d.dat", stage);
    if (fexistU(path, 0) == 0) {
        ok = 0;
    }
    if (ok == 0) {
        sprintf(path, "stage not found %d ", stage);
        putErr(path);
        OSReport("%s \n", path);
        stage = 3;
    }
    LoadStageNow(stage);
    if (fogG != 0) {
        setClear(fogG->color);
    }
    ZoidInitAll();
    ZoidCalcAll();
    ZoidVoiceScript();
    OSReport("ZoidVoiceScript -OK\n");
    if (GameMode.game_type != 5) {
        for (i = 1; i < 16; i++) {
            Zoid[i].slot = i & 1;
        }
    }
    for (i = 0; i < 16; i++) {
        z = &Zoid[i];
        if (z->joint != (void *)0) {
            ctrl = (Ctl3 *)z->anim_data;
            zdSearchPosPoly(z);
            if (0.0f == z->heading) {
                z->heading = 0.0349065848f;
            }
            zdOnGround(z);
            zdCoStartPos(z);
            zdCoStartPos(z);
            for (k = 0; k < 9; k++) {
                zdWeaponChg(z);
                if (z->selected_weapon_mount == -1) {
                    break;
                }
                t = ctrl->w[z->selected_weapon_mount];
                if (t == 2 || t == 2) {
                } else {
                    break;
                }
            }
        }
    }
    ZoidAmbientSetSkyAll();
    for (i = 0; i < 16; i++) {
        aiPrologue(i);
    }
    sCameraPurge();
    OSReport("cam purge GameMode.type=%d\n", GameMode.game_type);
    switch (GameMode.game_type) {
    case 2:
        sCamNN = 2;
        break;
    case 5:
        sCamNN = 4;
        break;
    default:
        sCamNN = 1;
        break;
    }
    if (sCamNN == 4) {
        sCameraSetQuat(&sCamera[0], 0);
        sCameraSetQuat(&sCamera[1], 1);
        sCameraSetQuat(&sCamera[2], 2);
        sCameraSetQuat(&sCamera[3], 3);
        if (Zoid[2].joint == 0) {
            OSReport("error Zoid[2] non\n");
            ZoidInit(&Zoid[2], 199);
        }
        if (Zoid[3].joint == 0) {
            OSReport("error Zoid[3] non\n");
            ZoidInit(&Zoid[3], 199);
        }
        sCamera[0].lights = Sky->lights;
        sCamera[1].lights = Sky->lights;
        sCamera[2].lights = Sky->lights;
        sCamera[3].lights = Sky->lights;
        sCameraTargetZoid(&sCamera[0], &Zoid[0]);
        sCameraTargetZoid(&sCamera[1], &Zoid[1]);
        sCameraTargetZoid(&sCamera[2], &Zoid[2]);
        sCameraTargetZoid(&sCamera[3], &Zoid[3]);
        sDispLoadParts(2, 0);
    }
    if (sCamNN == 2) {
        sCamNS2 = VsMode == 0;
        if (sCamNS2 != 0) {
            sCameraSetHalf2(&sCamera[0], 1);
            sCameraSetHalf2(&sCamera[1], 0);
        } else {
            sCameraSetHalf(&sCamera[0], 1);
            sCameraSetHalf(&sCamera[1], 0);
        }
        sCamera[0].lights = Sky->lights;
        sCamera[1].lights = Sky->lights;
        sCameraTargetZoid(&sCamera[0], &Zoid[0]);
        sCameraTargetZoid(&sCamera[1], &Zoid[1]);
        sDispLoadParts(2, 0);
    }
    if (sCamNN == 1) {
        sCameraSetNormal(&sCamera[0]);
        sCamera[0].lights = Sky->lights;
        sCameraTargetZoid(&sCamera[0], &Zoid[0]);
        sDispLoadParts(1, 0);
    }
    for (i = 0; i < 4; i++) {
        cam = &sCamera[i];
        if (cam->cobj != (void *)0 && (cz = cam->zoid) != (void *)0) {
            for (j = 0; j < 3; j++) {
                cam->v1f0[j] = 100.0f + cz->position[j];
                cam->v208[j] = 100.0f + cz->position[j];
                cam->v214[j] = 100.0f + cz->position[j];
            }
        }
    }
    gameStartF = 1;
    if (GameMode.game_type == 9) {
        gameStartF = 0;
    }
    gameStartTm = 0;
    sCameraSetShadowAll();
    HSD_VISetBlack(0);
    ZoidSetAnim(&Zoid[0], 1);
    ZoidSetAnim(&Zoid[1], 1);
    ZoidSetAnim(&Zoid[2], 1);
    ZoidSetAnim(&Zoid[3], 1);
    ZoidSetAnim(&Zoid[4], 1);
    ZoidSetAnim(&Zoid[5], 1);
    ZoidSetAnim(&Zoid[6], 1);
    ZoidSetAnim(&Zoid[7], 1);
    sEffectPrologue();
    sMissilePrologue();
    sLsrPrologue();
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != 0) {
            ctrl2 = (Ctl3 *)zoid->anim_data;
            zoid->weapon_mount = -1;
            idx = 9;
            for (cnt = 0; cnt < 10; cnt++, idx--) {
                if (idx < 0) {
                    idx = 9;
                }
                if (zoid->weapon_mounts[idx].active != 0) {
                    if (ctrl2 == 0) {
                        break;
                    }
                    f = ctrl2->w[idx];
                    if (f != 2) {
                        break;
                    }
                }
            }
            zoid->selected_weapon_mount = idx;
        }
    }
    OSReport("wp act no set     ---------------------------------------\n");
    winF = 0;
    GameMode.f3C = -1;
    OSReport("game0 ---- start voice----------------------------\n");
    camVoiceOn(Zoid[0].person, 2);
    OSReport("game0 ---- start voice end----------------------------------\n");
    gameTime = 36180;
    if (GameMode.game_type == 2 || GameMode.game_type == 3 || GameMode.game_type == 5) {
        vt = VsTimeTBL[VsTime];
        if (vt == -1) {
            gameTime = -1;
        } else {
            gameTime = vt * 60 * 60 + 59;
        }
    }
    if (GameMode.game_type == 4 || GameMode.game_type == 1) {
        gameTime = mgI.f308A * 60;
        if (gameTime == 0) {
            gameTime = 36180;
        } else {
            gameTime = gameTime + 59;
        }
    }
    if (GameMode.game_type == 9) {
        gameTime = -1;
    }
    OSReport("game0 ---- init----------------------------------\n");
    GameMode.win = 0;
    gameEndF = 0;
    GameMode.f30 = 0;
    gametime = 0;
    bpTm.a = 0;
    bpTm.b = 0;
    AreaIn = 0;
    AreaIn2 = 0;
    skip = 0;
    bpcnt = 0;
    cnt5 = 0;
    prevbp = 0;
    gameContinueTm = 660;
    IntSePrologue();
    dspLoadF = 0;
    tick = VIGetRetraceCount();
    last = tick;
    OSReport("main loop start   ----------------------------------------\n");
    while (1) {
        if (GameMode.f44 == 2) {
            break;
        }
        if (GameMode.f44 == 1 && (gametime > 3600 || gameEndF != 0)) {
            break;
        }
        vsyncN++;
        sPadAll();
        camTmp = sCamera;
        dummyFunc("g1p\n");
        vcStart();
        game1();
        vcEnd("game1");
        dummyFunc("g1e\n");
        if (bak[0] != gameEndF) {
            OSReport("gameEndF=%d\n", gameEndF);
        }
        bak[0] = gameEndF;
        if (gameEndF == 0 && gameStartF == 0) {
            gametime++;
        } else {
            Zoid[0].rumble_timer = 0;
            Zoid[1].rumble_timer = 0;
            *(u8 *)(sPad1 + 0x84) = 0;
            *(u8 *)(sPad2 + 0x84) = 0;
        }
        (void)idx;
        (void)idx;
        (void)idx;
        (void)idx;
        k = ~~tick;
        k = ~~tick;
        k = ~~tick;
        k = ~~tick;
        k = ~~tick;
        if (gameEndF == 5) {
            s32 tbl[15] = {480, 480, 900, 900, 900, 900, 480, 0, 0, 0, 0, 0, 0, 0, 0};
            dummyFunc("g1e5\n");
            cnt5++;
            if (cnt5 > tbl[GameMode.game_type]) {
                gameEndF = 6;
            }
            if (GameMode.game_type == 2 || GameMode.game_type == 3 || GameMode.game_type == 4 || GameMode.game_type == 5) {
                if (cnt5 > 120) {
                    if (*(s8 *)(sPad1 + 0x5d) != 0) {
                        gameEndF = 6;
                    }
                    if (GameMode.game_type == 2) {
                        if (*(s8 *)(sPad2 + 0x5d) != 0) {
                            gameEndF = 6;
                        }
                    }
                    if (GameMode.game_type == 5) {
                        if (*(s8 *)(sPad2 + 0x5d) != 0) {
                            gameEndF = 6;
                        }
                    }
                    if (GameMode.game_type == 5) {
                        if (*(s8 *)(sPad3 + 0x5d) != 0) {
                            gameEndF = 6;
                        }
                    }
                    if (GameMode.game_type == 5) {
                        if (*(s8 *)(sPad4 + 0x5d) != 0) {
                            gameEndF = 6;
                        }
                    }
                }
            }
        }
        if (gameEndF == 4) {
            dummyFunc("g1e4\n");
            winF = gameWin();
            gameEndF = 5;
            voiceSet(winF);
            motWinSet();
        }
        dummyFunc("g1ee\n");
        camTmp = &sCamera[0];
        dummyFunc("g1eMem\n");
        {
            void *ptrs[1024];
            C4 c1 = {200, 255, 200, 255};
            C4 c2 = {0, 0, 0, 50};
            C4 c3 = {0, 0, 255, 255};
            C4 c4 = {255, 0, 0, 100};
            s32 m1;
            s32 m2;
            s32 flag;
            s32 lim;
            s32 p;
            flag = 0;
            lim = 1024;
            for (p = 0; p < lim; p++) {
                ptrs[p] = 0;
            }
            for (p = 0; p < lim; p++) {
                ptrs[p] = OSAllocFromHeap(HSD_GetHeap(), 0x10000);
                if (ptrs[p] == (void *)0) {
                    break;
                }
            }
            m1 = p << 6;
            for (p = 0; p < lim; p++) {
                if (ptrs[p] != 0) {
                    HSD_Free(ptrs[p]);
                }
            }
            if (m1 >= 0x6000) {
                m1 -= 0x6000;
            }
            if (m1 <= 0x400) {
                flag = 1;
            }
            for (p = 0; p < lim; p++) {
                ptrs[p] = 0;
            }
            for (p = 0; p < lim; p++) {
                ptrs[p] = OSAllocFromHeap(usrHeap, 0x10000);
                if (ptrs[p] == (void *)0) {
                    break;
                }
            }
            m2 = p << 6;
            for (p = 0; p < lim; p++) {
                if (ptrs[p] != 0) {
                    OSFreeToHeap(usrHeap, ptrs[p]);
                }
            }
            if (m2 >= 0x6000) {
                m2 -= 0x6000;
            }
            if (m2 <= 0x2000) {
                flag = 1;
            }
            sprintf(str, "mem Sd%2dM%4dK,Us%2dM%4dK byte(s)", m1 / 1024, m1 & 0x3ff, m2 / 1024, m2 & 0x3ff);
        }
        dummyFunc("g1eDisp\n");
        pause = 0;
        for (;;) {
        dummyFunc("S ");
        if (vNow < 0) {
            vNow = 0;
        }
        while (vNowO != 0) {
            vNow++;
            if (vNow >= 60) {
                vNow -= 60;
            }
            vNowTBL[vNow] = 0;
            vNowO--;
        }
        now = VIGetRetraceCount();
        draw = 0;
        if (now - last >= a) {
            draw = 1;
        }
        if (now - tick < c || draw != 0) {
            last = now;
            vNowTBL[vNow] = 1;
            drawAll();
            sPutFontAllNn();
            HSD_VICopyXFB(0);
            HSD_VISetXFBDrawDone();
            if (VIGetRetraceCount() - tick < b) {
                VIWaitForRetrace();
            }
        }
        IntSeClear();
        now = tick;
        tick = VIGetRetraceCount();
        vNowO = tick - now;
        if (gameEndF < 1 && gameStartF == 0) {
            s32 oldpause;
            npads = 1;
            oldpause = pause;
            if (GameMode.game_type == 5) {
                npads = 4;
            }
            if (GameMode.game_type == 2) {
                npads = 2;
            }
            for (i = 0; i < npads; i++) {
                if (*(s8 *)(sPad[i] + 0x63) != 0) {
                    if (pause == i + 1) {
                        pause = 0;
                    } else if (pause == 0) {
                        if (Zoid[i].ai_active == 0 || i == 0) {
                            pause = i + 1;
                        }
                    }
                }
            }
            if (oldpause != pause) {
                SeOn(0x6c);
            }
        }
        if (pause != 0) {
            HSD_AudioSFXKeyOffAll();
            sDispPauseProc();
            vsyncN++;
            Zoid[0].rumble_timer = 0;
            Zoid[1].rumble_timer = 0;
            Zoid[2].rumble_timer = 0;
            Zoid[3].rumble_timer = 0;
            *(u8 *)(sPad1 + 0x84) = 0;
            *(u8 *)(sPad2 + 0x84) = 0;
            *(u8 *)(sPad3 + 0x84) = 0;
            *(u8 *)(sPad4 + 0x84) = 0;
            sPadAll();
            continue;
        }
        break;
        }
        if (gameEndF == 12) {
            break;
        }
        if (gameEndF == 8) {
            HSD_AudioSFXKeyOffAll();
            IntSeClose();
            switch (GameMode.game_type) {
            case 1:
                if (winF == 2 || winF == 3) {
                    *(u8 *)(sPad1 + 0x5d) = 0;
                    gameContinueTm = 660;
                    gameEndF = 9;
                    GameMode.win = 3;
                    sPadAll();
                } else {
                    gameEndF = 11;
                    setBpTBL();
                    d84 = 0;
                    d80 = 0;
                }
                break;
            case 4:
                GameMode.win = winF == 1 ? 2 : 3;
                gameEndF = 12;
                if (mgP == 0 || mgP->f321C == 0) {
                    if (GameMode.win != 3) {
                        gameEndF = 11;
                        setBpTBL();
                        d84 = 0;
                        d80 = 0;
                    }
                }
                break;
            default:
                gameEndF = 12;
                GameMode.win = winF == 1 ? 2 : 3;
                break;
            }
        }
        if (gameEndF == 9) {
            gameContinueTm--;
            if (gameContinueTm <= 0) {
                gameContinueTm = 0;
                gameEndF = 12;
            }
            if (gameContinueTm % 60 == 0 && gameContinueTm != 0) {
                SeOn(gameContinueTm <= 240 ? 0x91 : 0x90);
            }
            if (*(s8 *)(sPad1 + 0x59) != 0 || *(s8 *)(sPad1 + 0x5a) != 0) {
                s32 old = GameMode.win;
                if (*(s8 *)(sPad1 + 0x59) != 0) {
                    GameMode.win = 3;
                } else {
                    GameMode.win = 0;
                }
                if (old != GameMode.win) {
                    SeOn(0x6f);
                }
            }
            if (*(s8 *)(sPad1 + 0x5d) != 0) {
                gameContinueTm = 0;
                gameEndF = 10;
                SeOn(0x10);
            }
        }
        if (gameEndF == 11) {
            if (GameMode.win != 2) {
                gameEndF = 12;
            }
            if (GameMode.game_type != 1 && GameMode.game_type != 4) {
                gameEndF = 12;
            }
            if (mgP != 0 && mgP->f321C != 0) {
                gameEndF = 12;
            }
            if (gameEndF == 11) {
                if (putBP()) {
                    if (GameMode.game_type == 1) {
                        if (GameMode.map != 9) {
                            TEA_VoiceOn(15, 1);
                        }
                        gameEndF = 13;
                    } else {
                        gameEndF = 12;
                    }
                    IveSave[0x1c7f] = (s8)GameMode.f40;
                    IveSave[0x1c7e] += GameMode.f40;
                    IveSave[0x8f3f] = (s8)GameMode.f40;
                    IveSave[0x8f3e] += GameMode.f40;
                    OSReport("rank - now=%d sum=%d\n", (s8)IveSave[0x1c7f], (s8)IveSave[0x1c7e]);
                } else {
                    bpcnt++;
                    if (bpcnt > 15 && prevbp != bp[11]) {
                        bpcnt = 0;
                        TEA_SeKeyOn(0x21f, (u8)TEA_SEVOL, 64, 64);
                        prevbp = bp[11];
                    }
                }
                GameMode.f34 = bp[11];
            }
        }
        if (gameEndF == 13) {
            bpTm.b++;
            if (bpTm.b > 720) {
                gameEndF = 12;
            }
        }
    }
    HSD_FogSet(0);
    clearBlack();
    IntSeClose();
    VIWaitForRetrace();
    IntSeClear();
    IntSeClose();
    VIWaitForRetrace();
    IntSeClear();
    VIWaitForRetrace();
    VIWaitForRetrace();
    VIWaitForRetrace();
    GameMode.f30 = gametime / 60;
    tick = (*(u8 *)(sPad1 + 0x84) = 0);
    *(u8 *)(sPad2 + 0x84) = 0;
    *(u8 *)(sPad3 + 0x84) = 0;
    *(u8 *)(sPad4 + 0x84) = 0;
    i = 0;
    for (i = 0; i < 16; i++) {
        aiEpilogue(i);
    }
    sEffectEpilogue();
    sLsrEpilogue();
    sMissilePurgeAll();
    sMissileEpilogue();
    sDispPurgeParts();
    sCameraPurge();
    for (i = 0; i < 16; i++) {
        ZoidState *z2;
        z2 = &Zoid[i];
        if (z2->joint != (void *)0) {
            sWeaponUnMountAll(z2);
        }
    }
    ZoidPurgeAll();
    PurgeStageData();
    HSD_AudioSFXKeyOffAll();
    psKillAllGenerator();
    psKillAllParticle();
    clearBlack();
    fogG = 0;
    HSD_FogSet(0);
    i = ~~i;
    i = ~~i;
    TeaBgm(-1);
    gClear();
    dspLoadF = 1;
}
#pragma dont_inline on

#pragma force_active on
static s32 fixt[7366];

static const char lit_1551[26] = "StFixTbl size=%d tbl=%d \n";
s32 fixSt = -2128675072;
s32 fixEd = -2128609284;
s32 usrHeap = -1;
s32 ZoidsVs = -2146225736;
s32 strNameGame = -2143774896;
s32 strNameMake = -2143774888;
MgI3 * mgP = &mgI;
s32 gxWhite = -1;
typedef struct GXC { u8 r, g, b, a; } GXC;
GXC gxBack = {0, 0, 0, 0};
#pragma force_active off
s32 fixGet(void)
{
    s32 i = 0x50;
    s32 sum;
    s32 size = 0;
    u8 *p;
    i = 0;
    sum = 0;
    fix = (FixData *)fixt;
    size = fix->size;
    p = (u8 *)fix + 4;
    for (; i < size; i++) {
        sum += p[i];
    }
    ZeroMemory(&GameMode, 0x50);
    ZeroMemory(IveSaveFlag, 0x1cb0);
    ZeroMemory(IveSave, 0x1cb0);
    ZeroMemory(IveSave + 0x1cb0, 0x1cb0);
    ZeroMemory(IveSave + 0x3960, 0x1cb0);
    ZeroMemory(IveSave + 0x5610, 0x1cb0);
    ZeroMemory(IveSave + 0x72c0, 0x1cb0);
    if (fix->sum != sum) {
        return 0;
    }
    MemCpy((u8 *)fix + 8, &GameMode, 0x50);
    MemCpy((u8 *)fix + 0x58, IveSaveFlag, 0x1cb0);
    MemCpy((u8 *)fix + 0x1d08, IveSave, 0x1cb0);
    MemCpy((u8 *)fix + 0x39b8, IveSave + 0x1cb0, 0x1cb0);
    MemCpy((u8 *)fix + 0x5668, IveSave + 0x72c0, 0x1cb0);
    return 1;
}

static const char lit_1565[52] = "clear battle %d=====================flag[%d]=%02X \n";
static const char lit_1625[165] = "game loop start ============================GameMode.type=%d====\n================================\n===========================\n=====================================\n";
static const char lit_1626[13] = "debug/c_.dat";
static const char lit_1627[18] = "filter/filter.dat";
static const char lit_1628[22] = "GameMode.gametime=%d\n";
static const char lit_1629[28] = "ttlMain>> GameMode.type=%d\n";
static const char lit_1630[21] = "\n type=%d , stg=%d \n";
static const char lit_1631[26] = "epilogue?---------------\n";
static const char lit_1632[32] = "GameStartMain GameMode.type=%d\n";
static const char lit_1633[25] = "the end of the mission \n";
static const char lit_1634[13] = "stream off \n";
static const char lit_1635[12] = "audio off \n";
static const char lit_1636[9] = "key off\n";
static const char lit_1637[35] = "--------- main loop end ---------\n";
static const char lit_1639[16] = "mem arena %dk \n";
static const char lit_1650[33] = "memory arena error   lo==usrLO \n";
static const char lit_1651[53] = "keep alloc arena error usrHeap.....................\n";
static const char lit_1652[46] = "memomry arena heap ......................%dk\n";
static const char lit_1659[70] = "-------------------------------------test---------------------------\n";
static const char lit_1707[14] = "fixGet error\n";
static const char lit_1708[12] = "fixGet OK \n";
static const char lit_1709[15] = "resetcode=%X \n";
static const char lit_1710[16] = "dev mem alloc \n";
static const char lit_1711[18] = "ver %d %d %d %d \n";
static const char lit_1712[34] = "NowTime %d/%d/%d %02d:%02d:%02d \n";
static const char lit_1713[41] = "--------------test-----------ok--------\n";
static const char lit_1714[25] = "menu/loading/loading.dat";
static const char lit_1715[26] = "load ok=================\n";
static const char lit_1716[15] = "\n sound init \n";
static const char lit_1717[24] = "\n end sound def load  \n";
static const char lit_1718[35] = "mono !!--------------------------\n";
static const char lit_1719[26] = "menu/saveload/mc/icon.dat";
static const char lit_1720[9] = "icon ok\n";
static const char lit_1721[25] = "menu/caution/caution.dat";
static const char lit_1722[14] = "ptcl/Zoid_eff";
static const char lit_1723[17] = "forget partcle \n";
void batFlag(void)
{
    s32 n;
    s32 idx;
    s32 bit;
    if (GameMode.game_type == 1 && winF == 1) {
        n = GameMode.f24 + GameMode.map * 4;
        idx = n / 8 + 10;
        bit = n % 8;
        (IveSaveFlag + idx)[0x1c4e] |= bitTBL[bit];
        OSReport(lit_1565, n, idx, (s8)(IveSaveFlag + idx)[0x1c4e]);
    }
    (void)n; (void)n; (void)n; (void)idx; (void)idx;
}

void mainLoop(void)
{
    ModelArchive *arc;
    ModelArchive *arc2;
    s32 k;
    s32 i;
    F1 b;
    F1 a = {0.0f};
    b = a;
    HSD_VIData.f48 = b;
    OSReport(lit_1625, GameMode.game_type);
    arc = LoadArc2(lit_1626);
    if (arc != 0) {
        PurgeArc2(arc);
    }
    debugFileUnPurgeList();
    TeaBgm(-1);
    ascPrologue();
    dspFilter = LoadArc2(lit_1627);
    for (i = 0; i < 5; i++) {
        jobjFilter[i] = CopyJoint2(dspFilter, 0);
    }
    ZoidPrologue();
    GameZoidInit();
    sCamNN = 1;
    sCamNN2 = 2;
    sWeaponPrologue();
    zDispCursorPrologue();
    HSD_StateInvalidate(-1);
    lastGame = 0;
    OSReport(lit_1628, GameMode.f30);
    debugFileUnPurgeList();
    if (fogG != 0) {
        HSD_FogSet(0);
    }
    sPadRep = 1;
    HSD_SetZSortMode(0, 0);
    ttlMain();
    OSReport(lit_1629, GameMode.game_type);
    if (GameMode.game_type == 9) {
        GameMode.f44 = 1;
    } else {
        GameMode.f44 = 0;
    }
    sPadRep = 0;
    debugFileUnPurgeList();
    TeaBgm(-1);
    debugFileUnPurgeList();
    HSD_VISetBlack(0);
    OSReport(lit_1630, GameMode.game_type, GameMode.map);
    if (GameMode.game_type == 1) {
        loadMapInfo();
    }
    if (GameMode.game_type == 9) {
        k = 0;
        while (rdMapInfo(2, HSD_Randi(100)) == (void *)0) {
            k++;
            if (k > 1000) {
                return;
            }
        }
    }
    GameMode.f34 = 0;
    HSD_SetZSortMode(1, 1);
    zDispCursorEpilogue();
    TeaBgm(-1);
    HSD_StateInvalidate(-1);
    if (GameMode.game_type == 4) {
        if (GameMode.map == 0x64) {
            lastGame = 1;
        }
        OSReport(lit_1631);
    }
    OSReport(lit_1632, GameMode.game_type);
    arc2 = LoadArc2(lit_1626);
    if (arc2 != 0) {
        PurgeArc2(arc2);
    }
    debugFileUnPurgeList();
    VIWaitForRetrace();
    VIWaitForRetrace();
    VIWaitForRetrace();
    if (lastGame != 0) {
        Epilogue();
        allRank();
        OSReport(lit_1633);
    } else {
        TeaBgm(mgI.f3092);
        dspLoadF = 1;
        GameMode.f0C = -1;
        GameMode.f40 = 0;
        game0();
        batFlag();
    }
    if (GameMode.game_type == 1 && GameMode.map == 9 && winF == 1) {
        Epilogue();
        allRank();
        GameMode.win = 2;
    }
    if (GameMode.game_type == 2 || GameMode.game_type == 3 || GameMode.game_type == 5) {
        dspLoadF = 1;
    }
    waitV(3);
    GameMode.f38 = 0;
    if (GameMode.game_type == 9) {
        resetSkipOp();
    }
    if (GameMode.game_type == 9 && GameMode.f44 == 2) {
        GameMode.f38 = 1;
    }
    GameMode.f44 = 0;
    TeaBgm(-1);
    waitV(3);
    sWeaponEpilogue();
    ZoidEpilogue();
    for (i = 0; i < 5; i++) {
        jobjUnrefAll(jobjFilter[i]);
        jobjFilter[i] = 0;
    }
    PurgeArc2(dspFilter);
    dspFilter = 0;
    ascEpilogue();
    HSD_VISetBlack(0);
    sReadPre();
    chkVS();
    HSD_AudioStreamStop(0);
    OSReport(lit_1634);
    sReadPre();
    TeaBgm(-1);
    OSReport(lit_1635);
    sReadPre();
    HSD_AudioSFXKeyOffAll();
    OSReport(lit_1636);
    waitV(3);
    if (TeaSoundSfxLoadNum > 1) {
        TEA_SoundSfxPop();
    }
    OSReport(lit_1637);
}

void init_2(void)
{
    u8 *lo;
    u8 *hi;
    u8 *t;
    lo = (u8 *)(((u32)OSGetArenaLo() + 0x1f) & ~0x1f);
    if ((u32)lo == usrLO) {
        OSReport(lit_1650);
    }
    hi = (u8 *)OSGetArenaHi();
    if (OSGetPhysicalMemSize() == 0x3000000) {
        t = hi; t -= 0x1800000;
        if (t > lo) hi = t;
    }
    usrHeap = OSCreateHeap(lo, hi);
    if (usrHeap == -1) {
        OSReport(lit_1651);
    } else {
        OSReport(lit_1652, (hi - lo) / 1024);
    }
    (void)lo; (void)hi; (void)t; (void)t;
}

void main(void)
{
    s32 d9c = 0;
    s32 d98 = 0;
    s32 d94 = 0;
    s32 d90 = 0;
    s32 d8c = 0;
    f32 d88 = 0.0f;
    s32 d84 = 3;
    RM3 rm;
    OSCalendarTime ct;
    s32 ver0, ver1, ver2, ver3;
    F1 b;
    u32 n;
    s32 buffers_result;
    s32 mode_result;
    s32 heap_result;
    u32 lo;
    s32 again;
    static s32 queue[130];
    if (OSGetResetCode() == 0x80000000) {
        OSSetSaveRegion(fixSt, fixEd);
        fixSave();
    }
    init_alloc(2);
    sPadRep = 0;
    memcpy(&rm, GXNtsc480IntDf, 0x3c);
    buffers_result = HSD_SetInitParameter(1, 2);
    (void)buffers_result;
    mode_result = HSD_SetInitParameter(4, &rm);
    (void)mode_result;
    heap_result = HSD_SetInitParameter(5, 0x8c0000);
    (void)heap_result;
    HSD_Init();
    init_2();
    sFileInit();
    configClear();
    if ((u16)OSGetResetCode() == 0x8800) {
        GameMode.f38 = 1;
    }
    if (OSGetResetCode() == 0x80000000) {
        GameMode.f38 = 1;
    }
    if (GameMode.f38 == 1) {
        if (fixGet() == 0) {
            OSReport(lit_1707);
        } else {
            OSReport(lit_1708);
            configGet();
        }
        GameMode.f38 = 1;
        GameMode.game_type = 0;
    }
    OSReport(lit_1709, OSGetResetCode());
    lo = OSGetTime();
    GameMode.f48 += lo;
    GameMode.f48 = GameMode.f48 + 1;
    n = GameMode.f48;
    n &= 0xffff;
    goto c1;
b1:
    n -= 100000;
c1:
    if (n > 100000) goto b1;
    goto c2;
b2:
    n--;
    HSD_Randi(10);
c2:
    if (n != 0) goto b2;
    F1 a = {0.0f};
    b = a;
    HSD_VIData.f48 = b;
    fogG = 0;
    HSD_FogSet(0);
    if (OSGetPhysicalMemSize() == 0x3000000) {
        OSReport(lit_1710);
    }
    HSD_GetVersion(&ver0, &ver1, &ver2, &ver3);
    OSReport(lit_1711, ver0, ver1, ver2, ver3);
    OSTicksToCalendarTime(OSGetTime(), &ct);
    OSReport(lit_1712, ct.year, ct.mon, ct.mday, ct.hour, ct.min, ct.sec);
    debug11();
    HSD_PadInit(10, queue, 0, 0);
    sPadInit();
    VIWaitForRetrace();
    sPadAll();
    VIWaitForRetrace();
    sPadAll();
    HSD_VISetBlack(0);
    VIWaitForRetrace();
    sPadAll();
    VIWaitForRetrace();
    sPadAll();
    sFontInit();
    OSReport(lit_1713);
    debug11();
    debug11();
    debug11();
    dspLoad = LoadArc2(lit_1714);
    debug11();
    debug11();
    debug11();
    dspLoadF = 1;
    OSReport(lit_1715);
    sReadPre();
    debug11();
    TEA_SoundInit();
    OSReport(lit_1716);
    debug11();
    sReadPre();
    TEA_SoundDefLoad();
    debug11();
    OSReport(lit_1717);
    debug11();
    configGet();
    sReadPre();
    TEA_defstatusload();
    TEA_mcInit();
    if (OSGetSoundMode() == 0) {
        OSReport(lit_1718);
        sndOutputMode(0);
    }
    again = 0;
    if (again != 0) {
        sFontInit();
        dspLoad = LoadArc2(lit_1714);
        TEA_SoundDefLoad();
    }
    sCameraInit();
    menu_saveloadiconp = LoadArc2(lit_1719);
    OSReport(lit_1720);
    menu_yesnop = LoadArc2(lit_1721);
    dspLoadF = 0;
    while (1) {
        initPtcl();
        readPtcl(lit_1722);
        mainLoop();
        waitV(3);
        forgetPtcl();
        OSReport(lit_1723);
        HSD_AudioSFXKeyOffAll();
        TeaBgm(-1);
        waitV(3);
        TEA_AudioSeqStop();
        TEA_AudioSeqFree();
        if (TeaSoundSfxLoadNum > 1) {
            TEA_SoundSfxPop();
        }
        if (GameMode.game_type == 1 && GameMode.win == 0) {
            GameMode.f38 = 2;
        }
    }
}

s32 sdf[64];

}
