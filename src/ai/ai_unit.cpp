extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"
#include "zoid3.h"


//STRUCTS_BEGIN
typedef struct AiData3 {
    s32 f00;
    u8 pad_0004[0x10];
    s32 f14;
    u8 pad_0018[0x10];
    s32 f28;
    s32 f2C;
    s16 f30;
    s16 f32;
    s16 f34;
    s16 f36;
    s16 f38;
    s16 f3A;
    s16 f3C;
    s16 f3E;
    s16 f40;
    s16 f42;
    s16 f44;
    s16 f46;
    s16 f48;
    s16 f4A;
    s32 f4C;
    s16 f50;
    s16 f52;
    s32 f54;
    s32 f58;
    s32 f5C;
    s32 f60;
    s32 f64;
    s32 f68;
    s32 f6C;
    s16 f70;
    s16 f72;
    s16 f74;
    s16 f76;
    s16 f78;
    s16 f7A;
    s16 f7C;
    s16 f7E;
    s16 f80;
    s16 f82;
    s16 f84;
    s16 f86;
    s16 f88;
    u8 pad_008A[0x2];
    s32 f8C;
    s32 f90;
    s32 f94;
    s32 f98;
    s32 f9C;
    s32 fA0;
    s32 fA4;
    s16 fA8;
    s16 fAA;
    s16 fAC;
    s16 fAE;
    s16 fB0;
    s16 fB2;
    s16 fB4;
    s16 fB6;
    s16 fB8;
    u8 pad_00BA[0x2];
    s32 fBC;
    s32 fC0;
    s32 fC4;
    s16 fC8;
    s16 fCA;
    u32 fCC;
    s16 fD0;
    s16 fD2;
    s16 fD4;
    s16 fD6;
    s16 fD8;
    s16 fDA;
    s16 fDC;
    s16 fDE;
    s16 fE0;
    u8 pad_00E2[0x2];
    s32 fE4;
    s16 fE8;
    s16 fEA;
    s32 fEC;
} AiData3;
typedef char AiData3SizeCheck[sizeof(AiData3) == 0xF0 ? 1 : -1];
typedef struct TeaAi {
    s8 f00;
    u8 f01;
    u8 f02;
    u8 f03;
    u8 f04;
    s8 f05;
    u8 pad_0006[0x1];
    s8 f07;
    u8 pad_0008[0x1];
    s8 f09;
    u8 pad_000A[0x5];
    s8 f0F;
    s8 f10;
    s8 f11;
    s8 f12;
    s8 f13;
    u8 pad_0014[0x1];
    u8 f15;
    u8 f16;
    u8 f17;
    u8 f18;
    s8 f19;
    u8 pad_001A[0x7];
    u8 f21;
    u8 f22;
    u8 f23;
    u8 pad_0024[0x1];
    s8 f25;
    s8 f26;
    s8 f27;
    s16 f28;
    s8 f2A;
    u8 f2B;
    u8 pad_002C[0x2];
    s16 f2E;
    s16 f30;
    s16 f32;
    u8 f34;
    u8 pad_0035[0x1];
    s16 f36;
    s8 f38;
    u8 pad_0039[0x1];
    s16 f3A;
    s16 f3C;
    s16 f3E;
    u8 f40;
    u8 pad_0041[0x1];
    s16 f42;
    s16 f44;
    u8 pad_0046[0x2];
    s16 f48;
    s16 f4A;
    s16 f4C;
    u8 pad_004E[0x2];
    s16 f50;
    u8 pad_0052[0x2];
    s16 f54;
    u8 pad_0056[0x2];
    s16 f58;
    s16 f5A;
    s16 f5C;
    s16 f5E;
    s16 f60;
    s16 f62;
    s8 f64;
    u8 pad_0065[0x1];
    s16 f66[10];
    s16 f7A[10];
    u8 pad_008E[0x14];
    s16 fA2[10];
    s16 fB6[10];
    u8 pad_00CA[0x4];
    u8 fCE;
    u8 pad_00CF[0x1];
    s16 fD0;
    u8 pad_00D2[0x3];
    u8 fD5;
    s16 fD6;
    u8 pad_00D8[0x4];
    s8 fDC;
    s8 fDD;
    s16 fDE;
    u8 pad_00E0[0x2];
    u8 fE2;
    u8 pad_00E3[0x1];
    s16 fE4;
    u8 fE6;
    u8 pad_00E7[0x1];
    s16 fE8;
    s16 fEA;
    s16 fEC;
    u8 fEE;
    u8 fEF;
    s16 fF0;
    u8 fF2;
    u8 fF3;
    u8 pad_00F4[0x6C];
} TeaAi;
typedef char TeaAiSizeCheck[sizeof(TeaAi) == 0x160 ? 1 : -1];
typedef struct TeaPart {
    u8 pad_0000[0x5C];
    s32 f5C;
    u8 pad_0060[0xC4];
} TeaPart;
typedef char TeaPartSizeCheck[sizeof(TeaPart) == 0x124 ? 1 : -1];
typedef struct TeaBullet {
    u8 pad_0000[0xE];
    s16 f0E;
    u8 pad_0010[0x2];
    s16 f12;
    u8 pad_0014[0x16];
    s16 f2A;
    u8 pad_002C[0x20];
} TeaBullet;
typedef char TeaBulletSizeCheck[sizeof(TeaBullet) == 0x4C ? 1 : -1];
typedef struct ZoidAIState3 {
    s32 nearest[16];
    u8 pad_0040[0x34];
    s32 f74;
    u8 pad_0078[0x18];
    s32 f90;
    u8 pad_0094[0x16C];
} ZoidAIState3;
typedef char ZoidAIState3SizeCheck[sizeof(ZoidAIState3) == 0x200 ? 1 : -1];
//STRUCTS_END
typedef struct TeaRelay { s8 b0; u8 b1; s16 f02[20]; s16 f2A[20]; s16 f52[20]; s16 f7A[20]; s16 fA2[20]; u8 pad[0x194 - 0xCA]; } TeaRelay;
typedef char TeaRelaySizeCheck[sizeof(TeaRelay) == 0x194 ? 1 : -1];
extern TeaRelay Tea_relaydat[];
extern s32 sReadPre(void);
extern char *sprintf(char *buf, const char *fmt, ...);
extern s32 printf(const char *fmt, ...);
extern s32 puts(const char *s);
extern s32 fexistU(const char *path, s32 mode);
extern void *sReadFileU(const char *path, s32 mode);
extern void *memcpy(void *dst, const void *src, u32 size);
extern void free(void *p);
extern void zdAI_pointAng(s32 index, s32 a, s32 b, s32 *out_x, s32 *out_z);
extern void zdAI_goPoint(s32 index, f32 x, f32 z);
extern s32 zdAI_Look(s32 index);
extern f32 zdAI_lenPoint(s32 index, f32 x, f32 z);
extern void aiActSuspend_zoid(s16 index);
extern void zdAI_WaitMotion(s32 index, s32 motion);
extern s32 zdAI_IsAtack(s32 index);
extern void zdAI_Atack1(s32 index);
extern s32 aiObjectWall(s16 index, s16 degrees);
extern s16 aiNoWallSetPar(s16 index, s16 a);
extern void zdAI_RunAng(s32 index, s32 degrees);
extern void zdAI_StopAngRun(s32 index, s32 degrees);
typedef struct GameModeInfo3 { u8 pad_00[4]; s32 f04; s32 f08; } GameModeInfo3;
extern GameModeInfo3 GameMode;
extern f32 zdAI_goY(s32 index, s32 degrees, f32 distance);
extern void zdAI_Jump(s32 index);
extern s32 aiDontMove(s32 index);
extern void aiActFlightZoidLow(s16 index);
extern void aiActFlightZoidHigh(s16 index);
extern s32 zdAI_coHead(s32 index);
extern s32 zdAI_IsTurn(s32 index);
extern void zdAI_Step(s32 index, s32 degrees);
extern void zdAI_WeaponChgSlot(s32 index, s32 slot);
extern s32 zdAI_angPoint(s32 index, f32 x, f32 z);
extern void zdAI_SetLockZoid(s32 index);
extern s32 aiZoidRunTargetAttain(s16 index);
extern void aiZoidRun_ResetCommand(s16 index);
extern void zdAI_stopNow(s32 index);
extern void zdAI_setHigh(s32 index, s32 flag);
extern void aiZoidRunMode(s16 index, s16 a, s16 b, s16 c);
extern void zdAI_SetAngleON(s32 index, s32 degrees);
extern void zdAI_SetAngleSpd(s32 index, s32 speed);
extern void zdAI_SetLen(s32 index, f32 distance);
extern void zdAI_SetLenIn(s32 index, f32 distance);
extern void zdAI_SetLenOut(s32 index, f32 distance);
extern void DEV_EXPRINT(char *msg, s32 index);
extern void aiWepAtck(s16 index);
extern s32 zdAI_IsFire(s32 index);
extern s32 zdAI_IsTarget(s32 index);
extern s32 zdAI_IsAtackMineN(s32 index);
extern void aiOpt1Use(s16 index);
extern f64 __fabs(f64 value);
extern void aiWepChange(s16 index);
extern s32 aiActSuspend_Partner(s16 a, s16 b);
extern s32 aiActSuspend_FarWep(s16 index);
extern s32 aiActSuspend_SquarelyPerson(s16 index, s16 param);
extern void aiZoidRun(s16 index);
extern s32 zdAI_WarningArea(s32 index);
extern void zdAI_SetLenIn(s32 index, f32 distance);
extern s32 zdAI_goWall(s32 index, s32 distance, s32 degrees);
extern s32 zdAI_lenStep(s32 index);
extern s32 zdAI_freeAng(s32 index, s32 angle);
extern void aiZoidRunWallEscape(s16 index);
typedef struct TeaZoid { u8 pad_000[0x6C6]; s16 f6C6; u8 pad_6C8[0x7D2 - 0x6C8]; u8 f7D2; u8 pad_7D3[0x7FC - 0x7D3]; } TeaZoid;
extern TeaZoid Tea_zoiddat[];
extern void OSReport(const char *fmt, ...);
extern void ZeroMemory(void *address, u32 size);
extern void TEA_SetTimerInit(void);
extern s32 TEA_aitypeload(s16 index, s16 type);
extern void zdAI_setSpeed(s32 index, s32 speed);
extern s32 zdAI_WeaponSlotGetID(s32 index, s32 slot);
extern s32 zdAI_WeaponSlotBullet(s32 index, s32 slot);
extern s32 zdAI_cmpHigh(s32 index);
extern s32 aiWepSearchSlot(s32 index, s32 type_a, s32 type_b);
extern s16 aiNextWeaponScan(s32 index);
extern void aiWepChangeManual(s16 index);
extern s32 zdAI_SearchEnemy(s32 index);
extern s32 zdAI_AngZoidME2(s32 index, s32 target);
extern void zdAI_TargetSet(s32 index, s32 target);
extern void zdAI_SetZoid0(s32 index, s32 target);
extern s32 aiEnemyRaderSight(s16 index, s16 dist, s16 ang);
extern s32 aiEnemySupplement_AfterMove(s16 index);
extern void zdAI_rotPoint(s32 index, f32 x, f32 z, f32 distance, f32 angle);
extern void zdAI_WaitMotion(s32 index, s32 motion);
extern TeaAi Tea_aidat[];
extern TeaPart Tea_partsdat[];
extern TeaBullet Tea_bulletdat[];
extern s32 zdAI_WeaponGetID(s32 index);
extern void zdAI_WeaponFire1(s32 index);
extern void zdAI_WeaponFireON(s32 index);
extern s64 OSGetTime(void);
extern u32 __OSBusClock : 0x800000F8;
extern void aiZoidJump(s16 index);
extern void aiZoidStep(s16 index, s16 a);
extern void zdAI_Run(s32 index, s32 degrees);

extern s32 zdAI_WeaponChg(s32 index);
extern s32 zdAI_WeaponBullet(s32 index);

s32 aiEnemyRaderSight(s16 index, s16 dist, s16 ang);
s32 TEA_aitypeload(s16 index, s16 type);
s16 aiEnemySearch_ReturnDistance(s32 index);
s32 aiTerritoryCheck(s32 index);
void aiTargetFinalDestinationMode(s16 index);
void aiActOrbitChk(s32 index);
void aiZoidRunWallEscape(s16 index);
void aiZoidRunMode(s16 index, s16 a, s16 b, s16 c);
void aiZoidStep(s16 index, s16 deg);
void aiZoidJump(s16 index);
s32 aiActSuspend_FarWepStep(s16 index);
s32 aiActSuspend_FarWep(s16 index);
s32 aiActSuspend_EnemyAtck(s16 index);
s32 aiActSuspend_ObstaclePrecipice(s16 index, s16 param);
s32 aiActSuspend_Obstacle(s16 index, s16 param);
s32 aiActSuspend_SquarelyEnemy(s16 index);
s32 aiActSuspend_ZoidStoped(s16 index);
s32 aiActSuspend_EnemySupplement(s16 index);
void aiWepAtck(s16 index);
void aiWepAtckFire(s32 index);
s32 aiNextWeapon(s32 index);
void aiWepChange(s16 index);
void aiWepChangeManual(s16 index);
void aiGrapAtck(s16 index);
s32 aiActSuspend_ObstacleFlight(s16 index, s16 param);
void aiFlightProc(s32 index);
#pragma force_active on
AiData3 aiDat[16];
s32 aiCom[7];
s32 DEV_PRT_BUF[20];
#pragma force_active off
void aiActSuspend_zoid(s16 index)
{
    s32 result = 0;

    if (aiDat[index].f14 == 1) {
        aiDat[index].fAC = aiDat[index].fAA;
    }
    aiDat[index].f28 = 0;
    aiDat[index].f84 = Tea_aidat[index].f5E;
}

s32 aiActSuspend_Partner(s16 index, s16 partner)
{
    s32 result = 0;
    s16 current_partner = partner;

    s16 actor = 2;
    if (aiDontMove(actor)) {
        return 0;
    }
    return 0;
}

s32 aiEnemyRaderSight(s16 index, s16 dist, s16 ang)
{
    s32 result = 0;
    s32 front = 0;
    s32 wide = 0;

    if (ang > -30 && ang < 30) {
        front = 1;
    }
    if (ang > -120 && ang < 120) {
        wide = 1;
    }
    if ((s32)Tea_aidat[index].f21 == 1) {
        if (dist > 0 && dist < 9999) {
            result = 1;
        }
    }
    if ((s32)Tea_aidat[index].f23 == 1) {
        if (wide == 1) {
            if (dist <= Tea_aidat[index].f60) {
                result = 1;
            }
        } else {
            if (dist <= aiDat[index].f3E) {
                result = 1;
            }
        }
    }
    if ((s32)Tea_aidat[index].f22 == 1 && front == 1) {
        if (dist <= aiDat[index].f3E) {
            result = 1;
        }
    }
    aiDat[index].f54 = front;
    aiDat[index].f5C = wide;
    if (result == 1) {
        aiDat[index].fB6 = dist;
        aiDat[index].f3A = ang;
    }
    result = result;
    return result;
}

static const char lit_375[11] = "%d : %d : ";
void aiPrologue(s32 index)
{
    ZoidState *zoid;

    OSReport("AI Start \n");
    ZeroMemory(&aiDat[index], sizeof(AiData3));
    aiDat[index].f00 = 0;
    aiDat[index].f28 = 0;
    aiDat[index].f2C = 0;
    aiDat[index].f30 = 0;
    aiDat[index].f3C = 20;
    aiDat[index].f3E = 30;
    aiDat[index].f40 = 25;
    aiDat[index].f42 = 0;
    aiDat[index].f38 = 0;
    aiDat[index].f44 = 1;
    aiDat[index].f46 = 1;
    aiDat[index].f48 = 7;
    aiDat[index].f4A = 2;
    aiDat[index].f4C = 1;
    aiDat[index].f50 = 0;
    aiDat[index].f52 = 0;
    aiDat[index].f54 = 0;
    aiDat[index].f58 = 0;
    aiDat[index].f60 = 0;
    aiDat[index].f68 = 0;
    aiDat[index].f6C = 0;
    aiDat[index].f70 = 0;
    aiDat[index].f34 = 0;
    aiDat[index].f72 = 90;
    aiDat[index].f74 = 60;
    aiDat[index].f78 = 180;
    aiDat[index].f7A = 110;
    aiDat[index].f7C = 300;
    aiDat[index].f7E = 30;
    aiDat[index].f80 = 120;
    aiDat[index].f82 = 60;
    aiDat[index].f86 = -1;
    aiDat[index].f8C = 1;
    aiDat[index].f90 = 0;
    aiDat[index].f94 = 0;
    aiDat[index].f98 = 0;
    aiDat[index].f9C = 0;
    aiDat[index].fA0 = 0;
    aiDat[index].fA4 = 1;
    aiDat[index].fA8 = -1;
    aiDat[index].fAA = -1;
    aiDat[index].fAC = 0;
    aiDat[index].fAE = -1;
    aiDat[index].fB0 = 0;
    aiDat[index].fB2 = 0;
    aiDat[index].fB4 = 100;
    aiDat[index].fB8 = 0;
    aiDat[index].fBC = 1;
    aiDat[index].fC0 = 0;
    aiDat[index].fCA = 3000;
    aiDat[index].fC4 = 0;
    aiDat[index].f32 = -1;
    aiDat[index].fD6 = 0;
    aiDat[index].fD8 = 0;
    aiDat[index].f5C = 0;
    aiDat[index].fDA = 0;
    aiDat[index].fE8 = 0;
    aiDat[index].fDC = 0;
    aiDat[index].fEA = -1;
    aiDat[index].fEC = 0;
    TEA_SetTimerInit();
    if (index < 0) {
        return;
    }
    if (index >= 16) {
        return;
    }
    zoid = &Zoid[index];
    TEA_aitypeload(index, Zoid[index].field_20A0);
    aiDat[index].fEC = 0;
    aiDat[index].f30 = 0;
    aiDat[index].f3E = Tea_zoiddat[zoid->type].f6C6;
    aiDat[index].fD2 = zoid->option_type;
    zdAI_Look(index);
    aiDat[index].fCC = OSGetTime() / (__OSBusClock / 4);
    aiDat[index].fD0 = OSGetTime() / (__OSBusClock / 4) - aiDat[index].fCC;
    aiDat[index].fAA = -1;
    aiDat[index].fBC = 1;
    aiDat[index].f84 = 0;
    if ((s32)(s8)Tea_zoiddat[zoid->type].f7D2 == 1) {
        aiDat[index].fE4 = 1;
    } else {
        aiDat[index].fE4 = 0;
    }
    if (aiDontMove(index) == 0) {
        zdAI_Run(index, 0);
        zdAI_setSpeed(index, Tea_aidat[index].fF2);
    }
}

extern f32 zdAI_ComeMissile(s32 index);
extern f32 zdAI_ComeMissileAng(s32 index, s32 *out);
extern s32 zdAI_AngZoidEM(s32 index);
extern s32 zdAI_IsAtackMine(s32 index);
extern void zdAI_WeaponFireOFF(s32 index);
extern s32 aiActSuspend_EscTurn(s16 index);
extern s32 vcSeekMode;
typedef struct TeaAiX {
    u8 pad_0000[0x48];
    s16 f48;
    u8 pad_004A[0x4];
    s16 f4E;
    u8 pad_0050[0x2];
    s16 f52;
    u8 pad_0054[0x2];
    s16 f56;
    u8 pad_0058[0x74];
    s16 fCC;
    s16 fCE;
    s16 fD0;
    u8 pad_00D2[0x6];
    s16 fD8;
    s16 fDA;
    u8 pad_00DC[0x4];
    s16 fE0;
    u8 pad_00E2[0x7E];
} TeaAiX;
#define TEAX(i) (*(TeaAiX *)(Tea_aidat + i))
#pragma push
#pragma dont_inline off
#pragma auto_inline off
static inline s16 aiTeaDA(s32 i) { return TEAX(i).fDA; }
void ai(s32 index)
{
    char *mode_names[6] = { "\x96\xb3\x82\xb5", "\x94\xbc\x8c\x61\x93\xe0", "\x94\xbc\x8c\x61\x8a\x4f", "\x8a\x70\x93\x78\x88\xdb\x8e\x9d", "\x8e\xfc\x82\xe9", "" };
    char *cmd_names[8] = { "\x96\xb3\x82\xb5", "\x93\x47\x82\xf0\x92\x54\x82\xb7", "targetSet", "Next\x93\x47", "\x95\x90\x8a\xed\x95\xcf\x8d\x58", "\x82\x50\x94\xad\x8e\xcb", "\x8a\x69\x93\xac\x8d\x55\x8c\x82", "" };
    s32 unk28 = 0;
    f32 fl = 0.0f;
    s32 ang = 0;
    s32 unk16 = 0;
    s32 suspend = 1;
    ZoidAIState3 *aist;
    s32 dead = 0;
    ZoidState *zoid;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 100);

    if (index < 0) {
        return;
    }
    if (index >= 16) {
        return;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return;
    }
    aist = (ZoidAIState3 *)zoid->ai;
    dead = index;
    aiDat[index].f32 = zdAI_ComeMissile(index);
    if (aiDat[index].f32 != -1) {
        zdAI_ComeMissileAng(index, &ang);
        aiDat[index].f36 = ang;
    }
    aiDat[index].fB6 = aiEnemySearch_ReturnDistance(index);
    aiZoidRunTargetAttain(index);
    aiDat[index].f60 = 0;
    aiDat[index].f64 = 0;
    aiDat[index].f38 = zdAI_goY(index, 0, Tea_aidat[index].f48);
    if (aiDat[index].f38 > TEAX(index).fD0) {
        aiDat[index].f60 = 1;
    } else if (zdAI_goWall(index, Tea_aidat[index].f48, 0) == 1) {
        aiDat[index].f60 = 1;
    }
    if (aiDat[index].fE4 == 0) {
        if (aiDat[index].f38 < -TEAX(index).fD0) {
            aiDat[index].f60 = 1;
            aiDat[index].f64 = 1;
        }
    } else if (aiDat[index].f38 < 0) {
        aiDat[index].f38 = 0;
    }
    (void)(aiDat[index].f58 == 0);
    aiDat[index].f58 = 0;
    if (aiDat[index].fC0 == 1) {
        ang = zdAI_AngZoidEM(index);
        if (ang > -30 && ang < 30) {
            aiDat[index].f58 = 1;
        }
    }
    if (zdAI_IsAtackMine(index) == 1) {
        aiDat[index].f6C = 1;
    } else {
        aiDat[index].f6C = 0;
    }
    if (zoid->health == 0) {
        return;
    }
    if (aiDat[index].fD0 != (s16)(OSGetTime() / (__OSBusClock / 4) - aiDat[index].fCC)) {
        aiDat[index].fD0 = OSGetTime() / (__OSBusClock / 4) - aiDat[index].fCC;
        if (vcSeekMode == 0 && TEAX(index).fDA > 0 && aiTeaDA(index) < (s32)aiDat[index].fD0) {
            TEA_aitypeload(index, TEAX(index).fD8);
            aiDat[index].fCC = OSGetTime() / (__OSBusClock / 4);
            aiDat[index].fD0 = OSGetTime() / (__OSBusClock / 4) - aiDat[index].fCC;
            aiDat[index].fD8 = 0;
            aiDat[index].fB8 = 0;
            aiDat[index].fBC = 1;
            aiDat[index].f28 = 1;
            aiDat[index].f84 = 0;
            aiDat[index].fA8 = -1;
            aiDat[index].fAA = -1;
            aiDat[index].fAC = 0;
            aiDat[index].fAE = -1;
            aiDat[index].fB0 = 0;
            aiDat[index].fB2 = 0;
            aiDat[index].fB4 = 100;
            aiDat[index].fB8 = 0;
            aiDat[index].fBC = 1;
            aiDat[index].fC0 = 0;
            aiDat[index].fCA = 3000;
            aiDat[index].fC4 = 0;
            aiDat[index].f32 = -1;
            aiDat[index].fD6 = 0;
            aiDat[index].fD8 = 0;
            aiDat[index].f5C = 0;
            aiDat[index].fDA = 0;
            aiDat[index].fE8 = 0;
            aiDat[index].fDC = 0;
            aiDat[index].fEA = -1;
        }
    }
    if (aiDat[index].f30 > 0) {
        aiDat[index].f30--;
    }
    (void)(aiDat[index].fE4 == 0);
    if (aiDat[index].fE4 != 0) {
        if (aiDat[index].fE0 > 0) {
            aiDat[index].fE0--;
        } else if (aiDat[index].fE0 == 0) {
            aiDat[index].fE0 = -1;
        }
        if (aiDat[index].fDE > 0) {
            aiDat[index].fDE--;
        } else if (aiDat[index].fDE == 0) {
            aiDat[index].fDE = -1;
            aiDat[index].fE0 = TEAX(index).fE0;
        }
    }
    if (aiDat[index].f78 > 0) {
        aiDat[index].f78--;
    }
    if (aiDat[index].f74 > 0) {
        aiDat[index].f74--;
    }
    if (aiDat[index].f74 == 0) {
        zdAI_WeaponFireOFF(index);
        aiDat[index].f76 = TEAX(index).f56;
        aiDat[index].f74 = -1;
    }
    if (aiDat[index].f76 > 0) {
        aiDat[index].f76--;
    }
    if (aiDat[index].fB8 > 0) {
        aiDat[index].fB8--;
    }
    if (aiDat[index].f7E > 0) {
        aiDat[index].f7E--;
    }
    if (aiDat[index].f7E == 0) {
        aiDat[index].f80 = TEAX(index).f4E;
        aiDat[index].f7E = -1;
    }
    if (aiDat[index].f72 > 0) {
        aiDat[index].f72--;
    }
    if (aiDat[index].f80 > 0) {
        aiDat[index].f80--;
    }
    if (aiDat[index].f7A > 0) {
        aiDat[index].f7A--;
    }
    if (aiDat[index].f84 > 0) {
        aiDat[index].f84--;
    }
    if (aiDat[index].f86 > 0) {
        aiDat[index].f86--;
    }
    if (aiDat[index].f88 > 0) {
        aiDat[index].f88--;
    }
    if (aiDat[index].f84 == 0) {
        aiDat[index].f28 = 1;
        aiDat[index].f68 = 0;
        aiDat[index].f84 = -1;
        aiDat[index].f88 = TEAX(index).f52;
        aiDat[index].fD4 = TEAX(index).fCC;
    }
    if (aiDat[index].f86 == 0) {
        aiActSuspend_EscTurn(index);
        aiDat[index].f86 = -1;
    }
    if (aiDat[index].fD4 > 0) {
        aiDat[index].fD4--;
    }
    if (aiDat[index].f82 > 0) {
        aiDat[index].f82--;
    }
    if (zoid->health == zoid->field_0150) {
        aiDat[index].f52++;
    }
    if (zoid->health < zoid->field_0150) {
        aiDat[index].f52 = 0;
    }
    if (0.0f == zoid->speed) {
        aiDat[index].fDA++;
    } else {
        aiDat[index].fDA = 0;
    }
    if (aiDat[index].fE4 != 0) {
        aiFlightProc(index);
        return;
    }
    if (aiDat[index].f78 == 0) {
        aiWepChange(index);
    }
    if (aiDat[index].f76 == 0) {
        aiWepAtck(index);
    }
    aiGrapAtck(index);
    if (aiActSuspend_ObstaclePrecipice(index, zoid->speed) == 1) {
        return;
    }
    if (zdAI_IsTurn(index) != 0) {
        if (aiDat[index].f82 > 0) {
            return;
        }
        aiDat[index].f82 = 2;
        return;
    }
    aiTargetFinalDestinationMode(index);
    if (aiDat[index].fD6 > 0) {
        aiDat[index].fD6--;
    }
    if (aiDat[index].fD6 == 0) {
        aiDat[index].fD6 = -1;
        aiDat[index].fD8 = 0;
        aiDat[index].fB8 = 0;
        aiZoidRun_ResetCommand(index);
        return;
    }
    if (aiDat[index].fE8 > 0) {
        aiDat[index].fE8--;
    }
    if (aiDat[index].fE8 == 0) {
        aiDat[index].fE8 = -1;
        aiZoidRun_ResetCommand(index);
        return;
    }
    if (aiDat[index].fE8 <= 0) {
        suspend = aiActSuspend_Obstacle(index, zoid->speed);
    }
    aiActSuspend_FarWepStep(index);
    if (aiDat[index].fE8 <= 0 && suspend == 0 && aiTerritoryCheck(index) == 1) {
        return;
    }
    if (aiDat[index].f68 == 1 && aiDat[index].f64 == 1) {
        return;
    }
    aiActOrbitChk(index);
    if (aiDat[index].f82 > 0) {
        return;
    }
    if (index != 2 || aiActSuspend_Partner(aist->f90, aist->f74) == 0) {
        if (suspend == 0 && aiDat[index].fE8 <= 0) {
            dead = 1;
            suspend = aiActSuspend_EnemySupplement(index);
        }
    } else {
        return;
    }
    switch (aiDat[index].fEC) {
    case 0:
        if (aiActSuspend_SquarelyPerson(index, zoid->target_slot) != 0) {
            (void)0;
        } else {
            aiActSuspend_SquarelyEnemy(index);
        }
        aiDat[index].fEC++;
        break;
    case 1:
        aiActSuspend_FarWep(index);
        aiDat[index].fEC++;
        break;
    case 2:
        if (aiActSuspend_EnemyAtck(index) == 1) {
            (void)0;
        }
        aiDat[index].fEC++;
        break;
    case 3:
        aiDat[index].fEC++;
        break;
    case 4:
        if (0.0f == zoid->speed) {
            aiActSuspend_ZoidStoped(index);
        }
        aiDat[index].fEC++;
        break;
    case 5:
        if (zdAI_WarningArea(index) == 1 && aiDat[index].f30 <= 0) {
            aiActSuspend_zoid(index);
            if (aiDat[index].fC0 != 0) {
                zdAI_SetLenIn(index, 10.0f);
                if (aiDat[index].f76 == 0) {
                    aiWepAtck(index);
                }
            } else {
                zdAI_goPoint(index, 0.0f, 0.0f);
            }
            aiDat[index].f82 = 120;
            aiDat[index].f30 = 120;
            aiDat[index].f84 = 120;
        }
        aiDat[index].fEC++;
        break;
    default:
        if (suspend == 0) {
            aiZoidRun(index);
        }
        aiDat[index].fEC = 0;
        break;
    }
}
#undef TEAX
#pragma pop

s32 TEA_aitypeload(s16 index, s16 type)
{
    s32 dead = 0;
    char name[0x50];
    void *data;
    s16 t = type;

    sReadPre();
    sprintf(name, "etc/ai/ai_%04d.dat", t);
    if (fexistU(name, 0) == 0) {
        printf("AI-Open\202\305\202\253\202\310\202\242 %s", name);
        return 0;
    }
    data = sReadFileU(name, 0);
    memcpy(&Tea_aidat[index], data, 0x160);
    free(data);
    printf(name);
    puts("----------------------------------AI ReLoad--");
    sReadPre();
    sprintf(name, "etc/ai/relay_%04d.dat", (&Tea_aidat[index])->f36);
    if (fexistU(name, 0) == 0) {
        printf("Relay-Open\202\305\202\253\202\310\202\242 %s", name);
        return 0;
    }
    data = sReadFileU(name, 0);
    memcpy(&Tea_relaydat[index], data, 0x194);
    free(data);
    printf(name);
    puts("----------------------------------Relay ReLoad--");
    Tea_relaydat[index].b1 = 1;
    return 1;
}

s16 aiEnemySearch_ReturnDistance(s32 index)
{
    s32 i = 0;
    f32 fl = 0.0f;
    s32 st1 = 0;
    s32 st0 = 0;
    s32 x = 0;
    s32 y = 0;
    s32 tgt = 0;
    s32 z = 0;
    s32 mode = 0;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 100);

    z = z;
    z = z;
    mode = ((ZoidAIState3 *)Zoid[index].ai)->f90;
    if (mode == 0) {
        mode = 5;
    }
    i = 0;
    if (aiDat[index].f52 > Tea_aidat[index].f62) {
        aiDat[index].f54 = 0;
        aiDat[index].f5C = 0;
        aiDat[index].fC0 = 0;
    }
    if (aiDat[index].fE0 > 0) {
        aiDat[index].f54 = 0;
        aiDat[index].f5C = 0;
        aiDat[index].fC0 = 0;
        return 9999;
    }
    if (zdAI_SearchEnemy(index) != -1 && mode >= 3) {
        for (i = 0; i < 16; i++) {
            tgt = ((ZoidAIState3 *)Zoid[index].ai)->nearest[i];
            if (tgt == -1) {
                continue;
            }
            if (Zoid[index].slot != Zoid[tgt].slot && Zoid[tgt].health > 0) {
                if (tgt == Tea_aidat[index].fD6 || (s32)Tea_aidat[index].fD5 != 1 || index == Tea_aidat[index].fD6) {
                    x = Zoid[index].distances[tgt];
                    y = 360.0 * (Zoid[index].target_angles[tgt] / 6.2831852);
                    if (y < 0) {
                        z = y + 360;
                    } else {
                        z = y;
                    }
                    if (zdAI_goWall(index, x, z) == 0) {
                        aiDat[index].fC0 = aiEnemyRaderSight(index, x, y);
                        aiDat[index].fEA = -1;
                        if (aiDat[index].fC0 != 0) {
                            aiDat[index].fEA = tgt;
                            if (aiDat[index].fE4 != 0 && aiDat[index].fDE < 0 && aiDat[index].fE0 <= 0) {
                                aiDat[index].fDE = Tea_aidat[index].fDE;
                            }
                            if (aiEnemySupplement_AfterMove(index) && aiDat[index].f82 <= 0) {
                                zdAI_SetZoid0(index, tgt);
                            }
                            aiDat[index].f42 = zdAI_AngZoidME2(tgt, index);
                            zdAI_TargetSet(index, tgt);
                            return x;
                        }
                    }
                }
            }
        }
        if (mode == 3 || mode == 4) {
            tgt = Zoid[0].target_slot;
            if (aiDat[index].f82 <= 0) {
                if (tgt == -1) {
                    zdAI_SetZoid0(index, 0);
                } else {
                    zdAI_SetZoid0(index, tgt);
                }
            }
            if (tgt != -1) {
                zdAI_TargetSet(index, tgt);
            }
            if (tgt == -1) {
                aiDat[index].f42 = zdAI_AngZoidME2(0, index);
            } else {
                aiDat[index].f42 = zdAI_AngZoidME2(tgt, index);
            }
            aiDat[index].fC0 = 1;
            if (tgt == -1) {
                tgt = 0;
            }
            x = Zoid[index].distances[tgt];
            y = 360.0 * (Zoid[index].target_angles[tgt] / 6.2831852);
            if (y < 0) {
                (void)0;
            }
            aiEnemyRaderSight(index, x, y);
            aiDat[index].fB6 = x;
            aiDat[index].f3A = y;
            aiDat[index].fC0 = 1;
            return x;
        }
    } else if (mode < 3) {
        tgt = Zoid[0].target_slot;
        if (mode == 1) {
            if (aiDat[index].f82 <= 0) {
                if (tgt == -1) {
                    zdAI_SetZoid0(index, 0);
                } else {
                    zdAI_SetZoid0(index, tgt);
                }
            }
            if (tgt != -1) {
                zdAI_TargetSet(index, tgt);
            }
            if (tgt == -1) {
                aiDat[index].f42 = zdAI_AngZoidME2(0, index);
            } else {
                aiDat[index].f42 = zdAI_AngZoidME2(tgt, index);
            }
            aiDat[index].fC0 = 1;
        }
        if (mode == 2) {
            if (aiDat[index].f82 <= 0) {
                zdAI_SetZoid0(index, 0);
            }
            if (tgt != -1) {
                zdAI_TargetSet(index, tgt);
            }
        }
        if (tgt == -1) {
            tgt = 0;
        }
        x = Zoid[index].distances[tgt];
        y = 360.0 * (Zoid[index].target_angles[tgt] / 6.2831852);
        if (y < 0) {
            (void)0;
        }
        if (mode == 1) {
            aiEnemyRaderSight(index, x, y);
        }
        if (mode == 2) {
            aiDat[index].fC0 = aiEnemyRaderSight(index, x, y);
        }
        aiDat[index].fB6 = x;
        aiDat[index].f3A = y;
        aiDat[index].fC0 = 1;
        return x;
    }
    aiDat[index].f54 = 0;
    aiDat[index].f5C = 0;
    aiDat[index].fC0 = 0;
    zdAI_TargetSet(index, -1);
    return 9999;
}

s32 aiTerritoryCheck(s32 index)
{
    f32 dist = 0.0f;
    f32 x = 0.0f;
    f32 z = 0.0f;
    s16 d = 0;

    if (Tea_aidat[index].f3A == 0) {
        return 0;
    }
    if (aiDat[index].fD0 % 10 > 5) {
        return 0;
    }
    x = (f32)Tea_aidat[index].f3C;
    z = (f32)Tea_aidat[index].f3E;
    dist = zdAI_lenPoint(index, x, z);
    d = dist;
    if (Tea_aidat[index].f3A > d) {
        return 0;
    }
    if (aiDat[index].f52 < Tea_aidat[index].f62) {
        return 0;
    }
    (f32)(Tea_aidat[index].f3A / 2);
    aiActSuspend_zoid(index);
    zdAI_goPoint(index, x, z);
    aiDat[index].f82 = 300;
    aiDat[index].f68 = 0;
    dist = dist;
    return 1;
}

void aiTargetFinalDestinationMode(s16 index)
{
    s16 copy = index;
    s32 x = 0;
    s16 dead16 = 0;
    s32 z = 0;
    s32 d1 = 0;
    s32 angle = 0;
    s16 slot = 0;
    s32 d2 = 0;
    s32 d3 = 0;

    if ((s32)Tea_aidat[index].f34 == 1 && aiDat[index].fC0 == 0 && (slot = aiDat[index].fAA) != -1) {
        x = Tea_relaydat[index].f02[slot];
        z = Tea_relaydat[index].f2A[slot];
        angle = zdAI_angPoint(index, (f32)x, (f32)z);
        if (angle > 180) {
            angle = angle % 180 - 180;
        }
        d1 = (s32)zdAI_lenPoint(index, (f32)x, (f32)z);
        if (aiObjectWall(index, angle) == 0) {
            aiDat[index].f82 = 120;
            aiDat[index].f30 = 120;
            aiDat[index].f68 = 0;
            if (aiZoidRunTargetAttain(index)) {
                aiZoidRun_ResetCommand(index);
            } else {
                aiZoidRun_ResetCommand(index);
            }
            return;
        }
    }
    if (aiDat[index].fC0 == 1) {
        aiDat[index].fDC = 2;
        if (!aiDontMove(index)) {
            angle = aiDat[index].f3A;
            if (aiObjectWall(index, angle) == 1) {
                aiDat[index].fC0 = 0;
                aiDat[index].fB6 = 9999;
            } else if (aiDat[index].f30 <= 0) {
                if (aiDat[index].f82 > 0) {
                    zdAI_SetLockZoid(index);
                }
                aiDat[index].f82 = 0;
                d2 = 1;
                d3 = 1;
            }
        }
    }
    slot = slot;
}

void aiActOrbitChk(s32 index)
{
    s32 y = 0;
    s32 x = 0;
    s32 dist = 0;
    s32 dead = 0;

    if (aiDat[index].fC0 != 0 && Tea_aidat[index].f62 != 0 && (s32)aiDat[index].f52 >= (s32)Tea_aidat[index].f62 && Tea_aidat[index].f09 != 0) {
        dist = aiDat[index].fB6;
        if (dist <= (s32)(1.2 * (f64)aiDat[index].f3E)) {
            zdAI_pointAng(index, aiDat[index].f3A, dist, &y, &x);
            dead = 1;
            zdAI_goPoint(index, (f32)y, (f32)x);
            aiDat[index].f52 = 0;
            aiDat[index].f84 = 120;
            aiDat[index].f82 = 120;
            aiDat[index].f30 = 120;
        }
    }
}
void aiZoidRun(s16 index)
{
    s16 rnd1 = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 20 + 90);
    s16 zero = 0;
    s16 copy = index;
    s16 motion = 0;
    s16 count = 0;
    s32 p1 = 0;
    s32 p2 = 0;
    s16 rnd2 = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 110);
    s16 unused = 0; (void)unused;
    f32 scale = (f32)((((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 40 + 80) / 100);
    s16 rx = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 3000 - 1500);
    s16 rz = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 6251 / 2 - 1500);
    s16 len = 0;
    s16 slot = 0;
    s16 ang = 0;
    s16 dir = 0;

    if (aiDat[index].fB8 > 0) {
        return;
    }
    if (aiDat[index].fBC == 0 && (s32)(s8)Tea_aidat[index].f34 == 1) {
        return;
    }
    if (aiDat[index].f84 > 0) {
        return;
    }
    if ((s32)(s8)Tea_aidat[index].f2B == 1) {
        if (aiDat[index].fC0 == 1) {
            return;
        }
        aiDat[index].f14 = 0;
        p1 = rnd1 * Tea_aidat[index].f30;
        ang = p1 / 100;
        p2 = rnd1 * Tea_aidat[index].f2E;
        len = p2 / 100;
        switch (aiDat[index].fC8) {
        case 0:
            aiDat[index].fC8 = 1;
            aiDat[index].fB8 = scale * Tea_aidat[index].f32;
            break;
        case 1:
            zdAI_RunAng(index, ang);
            if (rnd2 < 100 - (Tea_aidat[index].f2A + 10)) {
                aiDat[index].fC8 = 2;
            }
            aiDat[index].fB8 = len;
            break;
        case 2:
            aiDat[index].fC8 = 3;
            aiDat[index].fB8 = scale * Tea_aidat[index].f32;
            break;
        case 3:
            zdAI_RunAng(index, -ang);
            if (rnd2 < 100 - (Tea_aidat[index].f2A + 10)) {
                aiDat[index].fC8 = 0;
            }
            aiDat[index].fB8 = len;
            break;
        case 4:
            aiDat[index].fC8 = 0;
            zdAI_goPoint(index, rx, rz);
            aiDat[index].fB8 = len;
        default:
            aiDat[index].fC8 = 0;
            aiDat[index].fB8 = 0;
            break;
        }
    } else {
        if ((s32)(s8)Tea_aidat[index].f34 == 1) {
            aiDat[index].f14 = 1;
            len = Tea_relaydat[index].b1;
            count = Tea_relaydat[index].b0;
            if (aiDat[index].fAA == -1) {
                aiDat[index].fAA = slot = 0;
                if (Tea_relaydat[index].b0 > 1) {
                    aiDat[index].fAC = 1;
                } else {
                    aiDat[index].fAC = -1;
                    if ((s32)(s8)Tea_relaydat[index].b1 == 1) {
                        aiDat[index].fAC = 0;
                    }
                }
                zdAI_goPoint(index, Tea_relaydat[index].f02[slot], Tea_relaydat[index].f2A[slot]);
                aiDat[index].fBC = 0;
            } else {
                slot = aiDat[index].fAC;
                if (slot != -1) {
                    aiDat[index].fAA = slot;
                    zdAI_goPoint(index, Tea_relaydat[index].f02[slot], Tea_relaydat[index].f2A[slot]);
                }
                slot = aiDat[index].fAC;
                if (slot > count || slot == -1) {
                    if ((s32)(s8)Tea_relaydat[index].b1 == 1) {
                        aiDat[index].fAC = 0;
                    } else {
                        aiDat[index].fAC = -1;
                    }
                }
                aiDat[index].fBC = 0;
            }
        }
        if (Tea_aidat[index].f38 == 1 && aiDat[index].f14 != 2) {
            aiDat[index].f14 = 2;
            if (Tea_aidat[index].f05 == 0) {
                dir = 20;
            } else {
                dir = -20;
            }
            if (Tea_aidat[index].f3A == 0) {
                if (!aiZoidRunTargetAttain(index)) {
                    zdAI_goPoint(index, Tea_aidat[index].f3C, Tea_aidat[index].f3E);
                }
            } else {
                zdAI_rotPoint(index, Tea_aidat[index].f3C, Tea_aidat[index].f3E, Tea_aidat[index].f3A, dir);
            }
        }
        if ((s32)(s8)Tea_aidat[index].f40 == 1 && aiDat[index].f14 != 3) {
            aiDat[index].f14 = 3;
            motion = Tea_aidat[index].f42;
            if (!aiZoidRunTargetAttain(index)) {
                zdAI_goPoint(index, Tea_aidat[index].f3C, Tea_aidat[index].f3E);
            } else {
                zdAI_WaitMotion(index, motion);
            }
        }
    }
}


void aiZoidRunWallEscape(s16 index)
{
    s32 d1 = 0;
    s16 copy = index;
    s16 e1 = 0;
    s16 e2 = 0;
    s16 e3 = 0;
    s32 y = 0;
    s32 x = 0;
    s16 angle = 0;
    s16 mode = 0;
    s16 sign = 1;

    if (Tea_aidat[index].f05 == 0) {
        mode = 0;
        sign = 1;
    }
    if ((s32)Tea_aidat[index].f05 == 1) {
        mode = 1;
        sign = -1;
    }
    if ((s32)Tea_aidat[index].f05 == 2) {
        mode = 2;
    }
    if (mode == 0 || mode == 1) {
        aiDat[index].f84 = 15;
        for (angle = 30; angle < 190; angle += 10) {
            if (aiObjectWall(index, angle * sign) == 0) {
                break;
            }
        }
        if (aiDat[index].fE4 != 0) {
            zdAI_RunAng(index, angle * sign);
        } else {
            zdAI_StopAngRun(index, angle * sign);
        }
        aiDat[index].f30 = 20;
        aiDat[index].f84 = 15;
    }
    if (mode == 2) {
        angle = aiNoWallSetPar(index, 12);
        if (aiDat[index].fE4 != 0) {
            zdAI_RunAng(index, angle);
        } else {
            zdAI_pointAng(index, angle, 200, &y, &x);
            zdAI_goPoint(index, (f32)y, (f32)x);
        }
        aiDat[index].f30 = 120;
        aiDat[index].f84 = 15;
        aiDat[index].f82 = 120;
    }
}

void aiZoidRunMode(s16 index, s16 a, s16 b, s16 c)
{
    s16 mode = a;
    s16 s1a = 0;
    s16 s18 = 1;
    s32 x14 = 0;
    s32 x10 = 0;
    s32 err = 0;
    s16 wep = 0;
    s16 bul = 0;
    s16 sign = 0;
    s16 sign2 = 0;
    s16 len = c;
    f64 d0;
    f64 d1;
    f64 d2;
    f64 d3;
    f64 d4;
    f64 d5;
    f64 d6;
    f64 d7;

    switch (b) {
    case 0:
        if (aiDat[index].fB6 < 9999 && aiDat[index].fB6 != -1) {
            d0 = (f64)aiDat[index].f42;
            if (__fabs(d0) < 30.0) {
                if (aiDat[index].fB6 > 300) {
                    zdAI_SetLenIn(index, 250.0f);
                    zdAI_SetAngleSpd(index, -40);
                } else if (aiDat[index].fB6 > 250) {
                    zdAI_SetLenIn(index, 200.0f);
                    zdAI_SetAngleSpd(index, 40);
                } else if (aiDat[index].fB6 > 200) {
                    zdAI_SetLenIn(index, 150.0f);
                    zdAI_SetAngleSpd(index, -30);
                } else if (aiDat[index].fB6 > 150) {
                    zdAI_SetLenIn(index, 100.0f);
                    zdAI_SetAngleSpd(index, 40);
                } else if (aiDat[index].fB6 > 100) {
                    zdAI_SetLenIn(index, 80.0f);
                    zdAI_SetAngleSpd(index, -50);
                } else if (aiDat[index].fB6 > 80) {
                    zdAI_SetLenIn(index, 50.0f);
                    zdAI_SetAngleSpd(index, 50);
                } else {
                    zdAI_SetLenIn(index, 1.0f);
                    if (aiDat[index].f42 < 0) {
                        zdAI_SetAngleON(index, -80);
                    } else {
                        zdAI_SetAngleON(index, 80);
                    }
                }
            } else if (aiDat[index].f84 > 0) {
                sign = aiDat[index].fB6;
                if ((s16)aiDat[index].fB6 < aiDat[index].f3E) {
                    zdAI_SetLenIn(index, 1.0f);
                    zdAI_SetAngleON(index, 180);
                } else {
                    zdAI_SetLenIn(index, (f32)aiDat[index].f3E);
                    if (Zoid[index].health < Zoid[index].field_0150) {
                        zdAI_SetAngleSpd(index, -30);
                    } else {
                        zdAI_SetAngleSpd(index, 10);
                    }
                }
                aiDat[index].f84 = Tea_aidat[index].f5E;
                aiDat[index].f84 = 180;
            } else {
                if (aiDat[index].f30 <= 0) {
                    zdAI_SetLenIn(index, (f32)aiDat[index].f3E);
                    zdAI_SetAngleON(index, 90);
                    aiDat[index].f30 = 240;
                } else {
                    zdAI_SetLenIn(index, (f32)aiDat[index].f3E);
                    zdAI_SetAngleON(index, 270);
                }
                aiDat[index].f84 = Tea_aidat[index].f5E;
                aiDat[index].f84 = 180;
            }
        } else {
            err = 1;
        }
        break;
    case 1:
        if (aiDat[index].fB6 < 9999 && aiDat[index].fB6 != -1) {
            if (aiDat[index].f88 <= 0) {
                d1 = (f64)aiDat[index].f42;
                if (__fabs(d1) < 30.0 && aiDat[index].fB6 < 120) {
                    if (aiDat[index].fB6 > 100) {
                        if (aiDat[index].f42 < 0) {
                            zdAI_SetAngleSpd(index, -50);
                        } else {
                            zdAI_SetAngleSpd(index, 50);
                        }
                    } else {
                        if (aiDat[index].f42 < 0) {
                            zdAI_SetAngleON(index, -120);
                        } else {
                            zdAI_SetAngleON(index, 120);
                        }
                    }
                    if (aiDat[index].fB6 < 40) {
                        zdAI_SetLenOut(index, 40.0f);
                    } else if (aiDat[index].fB6 < 60) {
                        zdAI_SetLenOut(index, 60.0f);
                    } else if (aiDat[index].fB6 < 80) {
                        zdAI_SetLenOut(index, 80.0f);
                    } else if (aiDat[index].fB6 < 100) {
                        zdAI_SetLenOut(index, 100.0f);
                    } else {
                        zdAI_SetLenOut(index, 120.0f);
                    }
                } else {
                    zdAI_SetLenOut(index, 100.0f);
                    d2 = (f64)aiDat[index].f42;
                    if (__fabs(d2) > 45.0) {
                        if (aiDat[index].f42 < 0) {
                            zdAI_SetAngleON(index, -120);
                        } else {
                            zdAI_SetAngleON(index, 120);
                        }
                    } else {
                        if (aiDat[index].f42 < 0) {
                            zdAI_SetAngleON(index, -90);
                        } else {
                            zdAI_SetAngleON(index, 90);
                        }
                    }
                }
                if (aiDat[index].f84 <= 0) {
                    aiDat[index].f84 = Tea_aidat[index].f5E;
                }
            }
        } else {
            err = 1;
        }
        break;
    case 2:
        zdAI_SetLockZoid(index);
        if (Tea_aidat[index].f05 == 0) {
            zdAI_SetAngleSpd(index, -10);
        } else {
            zdAI_SetAngleSpd(index, 10);
        }
        aiDat[index].f84 = Tea_aidat[index].f5E;
        break;
    case 3:
        if (aiDat[index].f64 != 0 || zdAI_coHead(index) != 0) {
            aiZoidRunWallEscape(index);
        } else {
            aiZoidRunWallEscape(index);
        }
        aiDat[index].f84 = 15;
        break;
    case 4:
        zdAI_SetAngleON(index, 180);
        aiDat[index].f84 = 18;
        break;
    case 5:
        if (aiDat[index].fB6 < 9999 && aiDat[index].fB6 != -1) {
            wep = zdAI_WeaponGetID(index);
            bul = Tea_partsdat[wep].f5C;
            zdAI_SetLenIn(index, (f32)Tea_bulletdat[bul].f0E);
            d3 = (f64)aiDat[index].f42;
            if (!(__fabs(d3) > 45.0)) {
                if (aiDat[index].f42 < 0) {
                    zdAI_SetAngleON(index, -90);
                } else {
                    zdAI_SetAngleON(index, 90);
                }
            }
            aiDat[index].f84 = Tea_aidat[index].f5E;
        } else {
            err = 1;
        }
        break;
    case 6:
        sign = 1;
        if (aiDat[index].fD0 % 30 < 15) {
            sign = -1;
        }
        if (aiDat[index].fB6 < 9999 && aiDat[index].fB6 != -1) {
            d4 = (f64)aiDat[index].f42;
            if (__fabs(d4) < 30.0 && len + 60 < aiDat[index].fB6) {
                if (aiDat[index].fB6 > 300) {
                    zdAI_SetLenIn(index, 250.0f);
                    zdAI_SetAngleSpd(index, -40);
                } else if (aiDat[index].fB6 > 250) {
                    zdAI_SetLenIn(index, 200.0f);
                    zdAI_SetAngleSpd(index, 40);
                } else if (aiDat[index].fB6 > 200) {
                    zdAI_SetLenIn(index, 150.0f);
                    zdAI_SetAngleSpd(index, -40);
                } else if (aiDat[index].fB6 > 150) {
                    zdAI_SetLenIn(index, 100.0f);
                    zdAI_SetAngleSpd(index, 40);
                } else if (aiDat[index].fB6 > 100) {
                    zdAI_SetLenIn(index, 80.0f);
                    zdAI_SetAngleSpd(index, -50);
                } else if (aiDat[index].fB6 > 80) {
                    zdAI_SetLenIn(index, 50.0f);
                    zdAI_SetAngleSpd(index, 50);
                } else {
                    zdAI_SetLenIn(index, 1.0f);
                    if (aiDat[index].f42 < 0) {
                        zdAI_SetAngleON(index, -90);
                    } else {
                        zdAI_SetAngleON(index, 90);
                    }
                }
            } else {
                zdAI_SetLen(index, (f32)len);
                zdAI_SetAngleSpd(index, sign * 10);
            }
            if (aiDat[index].f84 <= 0) {
                aiDat[index].f84 = Tea_aidat[index].f5E;
            }
            err = 0;
        } else {
            err = 1;
        }
        break;
    case 7:
        if (aiDat[index].fB6 < 9999 && aiDat[index].fB6 != -1) {
            if (aiDat[index].f30 <= 0) {
                sign = aiDat[index].fB6;
                if ((s16)aiDat[index].fB6 <= aiDat[index].f3E) {
                    zdAI_Look(index);
                    aiDat[index].f30 = 240;
                } else {
                    zdAI_SetLenIn(index, (f32)aiDat[index].f3E);
                    d5 = (f64)aiDat[index].f42;
                    if (!(__fabs(d5) > 45.0)) {
                        if (aiDat[index].f42 < 0) {
                            zdAI_SetAngleON(index, 80);
                        } else {
                            zdAI_SetAngleON(index, -80);
                        }
                    }
                }
                aiDat[index].f84 = Tea_aidat[index].f5E;
            }
        } else {
            err = 1;
        }
        break;
    case 8:
        sign2 = 1;
        if (aiDat[index].fD0 % 30 < 15) {
            sign2 = -1;
        }
        if (aiDat[index].fB6 < 9999 && aiDat[index].fB6 != -1) {
            if (len - 40 > aiDat[index].fB6) {
                if (aiDat[index].fB6 < 100) {
                    d6 = (f64)aiDat[index].f42;
                    if (__fabs(d6) < 30.0) {
                        if (aiDat[index].f42 < 0) {
                            zdAI_SetAngleON(index, -120);
                        } else {
                            zdAI_SetAngleON(index, 120);
                        }
                    } else {
                        if (aiDat[index].f42 < 0) {
                            zdAI_SetAngleSpd(index, -50);
                        } else {
                            zdAI_SetAngleSpd(index, 50);
                        }
                        zdAI_SetLen(index, (f32)len);
                        if (aiDat[index].f84 <= 0) {
                            aiDat[index].f84 = Tea_aidat[index].f5E;
                        }
                        break;
                    }
                } else {
                    if (aiDat[index].f42 < 0) {
                        zdAI_SetAngleON(index, -120);
                    } else {
                        zdAI_SetAngleON(index, 120);
                    }
                }
                if (aiDat[index].fB6 < 40) {
                    zdAI_SetLenOut(index, 40.0f);
                } else if (aiDat[index].fB6 < 60) {
                    zdAI_SetLenOut(index, 60.0f);
                } else if (aiDat[index].fB6 < 80) {
                    zdAI_SetLenOut(index, 80.0f);
                } else if (aiDat[index].fB6 < 100) {
                    zdAI_SetLenOut(index, 100.0f);
                } else {
                    zdAI_SetLenOut(index, 120.0f);
                }
            } else if (len + 40 < aiDat[index].fB6) {
                if (aiDat[index].fB6 > 300) {
                    zdAI_SetLenIn(index, 300.0f);
                    zdAI_SetAngleSpd(index, -50);
                } else if (aiDat[index].fB6 > 250) {
                    zdAI_SetLenIn(index, 250.0f);
                    zdAI_SetAngleSpd(index, 50);
                } else if (aiDat[index].fB6 > 200) {
                    zdAI_SetLenIn(index, 200.0f);
                    zdAI_SetAngleSpd(index, -40);
                } else if (aiDat[index].fB6 > 150) {
                    zdAI_SetLenIn(index, 150.0f);
                    zdAI_SetAngleSpd(index, 40);
                } else if (aiDat[index].fB6 > 120) {
                    zdAI_SetLenIn(index, 120.0f);
                    zdAI_SetAngleSpd(index, -50);
                } else if (aiDat[index].fB6 > 100) {
                    zdAI_SetLenIn(index, 100.0f);
                    zdAI_SetAngleSpd(index, 50);
                } else if (aiDat[index].fB6 > 80) {
                    zdAI_SetLenIn(index, 80.0f);
                    zdAI_SetAngleSpd(index, -50);
                } else if (aiDat[index].fB6 > 60) {
                    zdAI_SetLenIn(index, 60.0f);
                    zdAI_SetAngleSpd(index, 50);
                } else if (aiDat[index].fB6 > 40) {
                    zdAI_SetLenIn(index, 40.0f);
                    zdAI_SetAngleSpd(index, -50);
                } else {
                    zdAI_SetLenIn(index, 1.0f);
                    if (aiDat[index].f42 < 0) {
                        zdAI_SetAngleON(index, -120);
                    } else {
                        zdAI_SetAngleON(index, 120);
                    }
                }
            } else {
                zdAI_SetLen(index, (f32)len);
                d7 = (f64)aiDat[index].f42;
                if (__fabs(d7) < 30.0) {
                    if (aiDat[index].f42 < 0) {
                        zdAI_SetAngleON(index, -120);
                    } else {
                        zdAI_SetAngleON(index, 120);
                    }
                } else {
                    if (aiDat[index].f42 < 0) {
                        zdAI_SetAngleSpd(index, -50);
                    } else {
                        zdAI_SetAngleSpd(index, 50);
                    }
                }
            }
            if (aiDat[index].f84 <= 0) {
                aiDat[index].f84 = Tea_aidat[index].f5E;
            }
            err = 0;
        } else {
            err = 1;
        }
        break;
    default:
        DEV_EXPRINT("AIMODE \x83R\x83}\x83\x93\x83hERR\n", index);
        break;
    }
    if (err == 1) {
        aiDat[index].fD8 = 0;
        aiDat[index].fB8 = 0;
        aiZoidRun_ResetCommand(index);
    }
}

void aiZoidStep(s16 index, s16 deg)
{
    s16 five = 5;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 20 + 90);
    (((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 360);
    s16 a2 = 0;
    s16 a1;
    s16 ang;
    s32 dist;
    s32 gm = 0;

    dist = dist;
    if (aiDat[index].f7A <= 0) {
        if ((s32)Tea_aidat[index].fCE == 1) {
            aiDat[index].f7A = Tea_aidat[index].f5C;
            aiDat[index].fD8++;
        } else {
            dist = zdAI_lenStep(index);
            if (deg >= 0) {
                ang = deg;
            } else {
                ang = deg + 360;
            }
            gm = 0;
            if (GameMode.f04 == 2 && GameMode.f08 == 1) {
                gm = 1;
            }
            if (aiDat[index].fE4 != 0) {
                gm = 0;
            }
            if (gm == 0) {
                a1 = zdAI_goY(index, ang, (f32)dist);
            } else {
                a1 = zdAI_goY(index, ang, (f32)(0.5 * (f32)dist));
                a2 = zdAI_goY(index, ang, (f32)(1.5 * (f32)dist));
            }
            if (zdAI_goWall(index, Tea_aidat[index].f48, ang) == 1) {
                return;
            }
            if (gm == 0) {
                if (a1 < -Tea_aidat[index].fD0) {
                    return;
                }
            } else {
                if (a1 < -Tea_aidat[index].fD0) {
                    return;
                }
                if (a2 < -Tea_aidat[index].fD0) {
                    return;
                }
                if ((s16)zdAI_goY(index, ang - 10, (f32)dist) < -Tea_aidat[index].fD0) {
                    return;
                }
                if ((s16)zdAI_goY(index, ang + 10, (f32)dist) < -Tea_aidat[index].fD0) {
                    return;
                }
            }
            zdAI_Step(index, deg);
            aiDat[index].f7A = Tea_aidat[index].f5C;
            aiDat[index].fD8++;
        }
    }
}

void aiZoidJump(s16 index)
{
    s32 dist = 0;
    s32 flag = 0;

    if ((s32)Tea_aidat[index].fCE != 1) {
        flag = 0;
        if (GameMode.f04 == 2 && GameMode.f08 == 1) {
            flag = 1;
            dist = zdAI_lenStep(index);
        }
        if (aiDat[index].fE4 != 0) {
            flag = 0;
        }
        if (aiDat[index].f72 <= 0) {
            if (flag != 0) {
                if ((s16)zdAI_goY(index, 0, (f32)dist) < -Tea_aidat[index].fD0) {
                    return;
                }
                if ((s16)zdAI_goY(index, 180, (f32)dist) < -Tea_aidat[index].fD0) {
                    return;
                }
                if ((s16)zdAI_goY(index, 90, (f32)dist) < -Tea_aidat[index].fD0) {
                    return;
                }
                if ((s16)zdAI_goY(index, 270, (f32)dist) < -Tea_aidat[index].fD0) {
                    return;
                }
            }
            zdAI_Jump(index);
            aiDat[index].f72 = Tea_aidat[index].f5A;
        }
    }
}

s32 aiActSuspend_FarWepStep(s16 index)
{
    s32 range = 0;
    s32 result = 0;

    range = Tea_aidat[index].f44;
    if (range < 40) {
        range = 50;
    }
    if (aiDat[index].f32 == -1 || aiDat[index].f32 == 9999) {
        return 0;
    }
    if (aiDat[index].f32 > range) {
        return 0;
    }
    if (aiDontMove(index)) {
        return 0;
    }
    if (aiDat[index].fE4 != 0) {
        aiZoidStep(index, 90);
        aiOpt1Use(index);
        return 0;
    }
    if (Tea_aidat[index].f19) {
        if (aiDat[index].fB6 >= 9999 || aiDat[index].fB6 == -1) {
            aiOpt1Use(index);
            aiZoidStep(index, (Tea_aidat[index].f4A + aiDat[index].f36) % 360);
        } else if (aiDat[index].fB6 > (s32)(1.2 * (f64)aiDat[index].f3E)) {
            aiOpt1Use(index);
            aiZoidStep(index, (Tea_aidat[index].f4A + aiDat[index].f36) % 360);
        } else {
            f64 diff = (f64)aiDat[index].f42;
            if (__fabs(diff) < 30.0) {
                aiOpt1Use(index);
                if (aiDat[index].f3A < 0) {
                    aiZoidStep(index, aiDat[index].f3A % 360 + 360);
                } else {
                    aiZoidStep(index, aiDat[index].f3A % 360);
                }
            } else {
                aiOpt1Use(index);
                aiZoidStep(index, (Tea_aidat[index].f4A + aiDat[index].f36) % 360);
            }
        }
        result = 1;
    }
    return result;
}

s32 aiActSuspend_FarWep(s16 index)
{
    s32 range = 50;
    s32 result = 0;

    range = Tea_aidat[index].f44;
    if (range < 40) {
        range = 50;
    }
    if (aiDat[index].f32 == -1 || aiDat[index].f32 == 9999) {
        return 0;
    }
    if (aiDat[index].f32 > range) {
        return 0;
    }
    if (aiDat[index].fE4 != 0 && Tea_aidat[index].fDC && Tea_aidat[index].fDD) {
        zdAI_setHigh(index, 1);
    }
    if ((s32)Tea_aidat[index].f18 == 1) {
        aiOpt1Use(index);
        if (aiDat[index].fC0 == 0) {
            aiActSuspend_zoid(index);
            if (aiDat[index].fE4 != 0) {
                zdAI_Run(index, (aiDat[index].f36 + 180) % 360);
            } else {
                zdAI_RunAng(index, aiDat[index].f36);
            }
            aiWepAtck(index);
            result = 1;
            if ((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000) % 100 == 0) {
                return result;
            }
        }
        aiWepAtck(index);
    }
    if (aiDontMove(index)) {
        return 0;
    }
    if ((s32)Tea_aidat[index].f15 == 1 && aiDat[index].f88 <= 0) {
        aiActSuspend_zoid(index);
        if (aiDat[index].fC0 != 0) {
            aiZoidRunMode(index, -1, 2, -1);
            aiDat[index].f30 = 180;
            aiDat[index].f82 = Tea_aidat[index].f50;
            result = 1;
        } else {
            if (aiDat[index].fE4 != 0) {
                zdAI_Run(index, (aiDat[index].f36 + 180) % 360);
            } else {
                zdAI_StopAngRun(index, aiDat[index].f36);
            }
            aiDat[index].f30 = 180;
            aiDat[index].f82 = Tea_aidat[index].f50;
        }
    }
    if ((s32)Tea_aidat[index].f16 == 1) {
        aiActSuspend_zoid(index);
        if (aiDat[index].fC0 != 0) {
            aiZoidRunMode(index, -1, 0, -1);
            aiDat[index].f30 = 180;
            aiDat[index].f82 = 180;
            result = 1;
        } else {
            if (aiDat[index].fE4 != 0) {
                zdAI_Run(index, (aiDat[index].f36 + 180) % 360);
            } else {
                zdAI_StopAngRun(index, aiDat[index].f36);
            }
            aiDat[index].f30 = 180;
            aiDat[index].f82 = 180;
        }
        if (aiDat[index].fD2 < 4) {
            aiOpt1Use(index);
        }
    }
    if ((s32)Tea_aidat[index].f17 == 1) {
        if (aiDat[index].f88 <= 0) {
            aiActSuspend_zoid(index);
            aiZoidRunMode(index, -1, 1, -1);
            aiDat[index].f30 = 180;
            aiDat[index].f82 = Tea_aidat[index].f50;
            result = 1;
        }
        aiOpt1Use(index);
    }
    return result;
}

s32 aiActSuspend_EnemyAtck(s16 index)
{
    s32 result = 0;
    s16 mine = 0;
    s16 ang = aiDat[index].f3A;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 360);

    if (aiDat[index].f6C == 0) {
        return 0;
    }
    mine = zdAI_IsAtackMineN(index);
    if (mine == -1) {
        return 0;
    }
    if ((s32)Tea_aidat[index].f23 == 1 && aiDat[index].fC0 == 0) {
        return 0;
    }
    if (Tea_aidat[index].f11) {
        aiWepAtck(index);
        if (aiDat[index].fD2 == 5) {
            aiOpt1Use(index);
        }
    }
    if (aiDontMove(index)) {
        return 0;
    }
    if (aiDat[index].fE4 != 0 && Tea_aidat[index].fDC && Tea_aidat[index].fDD) {
        zdAI_setHigh(index, 1);
    }
    if (Tea_aidat[index].f0F && aiDat[index].f72 <= 0) {
        if (aiDat[index].fD2 == 1) {
            aiOpt1Use(index);
        }
        if (aiDat[index].fD2 == 5) {
            aiOpt1Use(index);
        }
        zdAI_Jump(index);
        aiDat[index].f72 = Tea_aidat[index].f5A;
    }
    if (Tea_aidat[index].f10) {
        if (aiDat[index].fD2 == 1) {
            aiOpt1Use(index);
        }
        if (aiDat[index].f7A <= 0) {
            aiZoidStep(index, ang);
        }
    }
    if (Tea_aidat[index].f12) {
        if (aiDat[index].fD4 <= 0) {
            aiActSuspend_zoid(index);
            aiZoidRunMode(index, -1, 1, -1);
            result = 1;
        }
        if (aiDat[index].fD2 != 1) {
            aiOpt1Use(index);
        }
    }
    if (Tea_aidat[index].f13 && aiDat[index].fD6 <= 0) {
        aiDat[index].f86 = Tea_aidat[index].f5E;
    }
    return result;
}

s32 aiActSuspend_ObstaclePrecipice(s16 index, s16 param)
{
    s32 first = 0;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 360);
    s16 copy = param;
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;

    if (aiDontMove(index)) {
        return 0;
    }
    if (aiDat[index].fE4 != 0) {
        return 0;
    }
    if (aiDat[index].f64 == 1) {
        if (zdAI_IsTurn(index) == 0) {
            aiActSuspend_zoid(index);
            if ((s16)zdAI_goY(index, 0, (f32)Tea_aidat[index].f48) < -Tea_aidat[index].fD0) {
                zdAI_stopNow(index);
                zdAI_StopAngRun(index, aiNoWallSetPar(index, 20));
                aiDat[index].f68 = 1;
                aiDat[index].f82 = 120;
            }
        } else {
            if ((s16)zdAI_goY(index, 0, (f32)(Tea_aidat[index].f48 * 2)) < -Tea_aidat[index].fD0) {
                zdAI_Run(index, (s32)(1.5 * (f64)aiNoWallSetPar(index, 20)));
                return 1;
            }
            if ((s16)zdAI_goY(index, 0, (f32)Tea_aidat[index].f48) < -Tea_aidat[index].fD0) {
                zdAI_stopNow(index);
                zdAI_StopAngRun(index, aiNoWallSetPar(index, 20));
            }
        }
        return 1;
    }
    return 0;
}

s32 aiActSuspend_Obstacle(s16 index, s16 param)
{
    s32 result = 0;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 360);
    s16 copy = param;
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;

    if (aiDontMove(index)) {
        return 0;
    }
    if (aiDat[index].f68 == 1) {
        if (aiDat[index].f60 == 0) {
            aiDat[index].f68 = 0;
            if (zdAI_IsTurn(index) == 0) {
                aiActSuspend_zoid(index);
                zdAI_Run(index, 0);
                aiDat[index].f30 = 180;
                aiDat[index].f82 = 180;
                result = 0;
                param = param;
                if ((s32)Tea_aidat[index].f34 == 1) {
                    aiDat[index].f82 = 60;
                }
            } else {
                aiActSuspend_zoid(index);
                zdAI_Run(index, 0);
                aiDat[index].f30 = 60;
                aiDat[index].f82 = 30;
                result = 0;
                param = param;
                if ((s32)Tea_aidat[index].f34 == 1) {
                    aiDat[index].f82 = 60;
                }
            }
            return 0;
        }
    } else if (aiDat[index].f60 == 0) {
        aiDat[index].f68 = 0;
    }
    if (aiDat[index].f60 == 1) {
        if (aiDat[index].f64 == 0) {
            if (zdAI_coHead(index)) {
                if (zdAI_IsTurn(index) == 0) {
                    zdAI_StopAngRun(index, aiNoWallSetPar(index, 30));
                    aiDat[index].f82 = 120;
                    aiDat[index].f30 = 120;
                    return 1;
                }
            } else {
                if (aiDat[index].f30 > 0) {
                    return 0;
                }
                if (param == 0) {
                    if (aiDat[index].fDA > 180) {
                        aiActSuspend_zoid(index);
                        aiZoidRunWallEscape(index);
                        aiDat[index].f82 = 120;
                    } else if (zdAI_IsTurn(index) == 0) {
                        aiActSuspend_zoid(index);
                        zdAI_StopAngRun(index, aiNoWallSetPar(index, 30));
                        aiDat[index].f82 = 120;
                    }
                } else {
                    aiActSuspend_zoid(index);
                    zdAI_Run(index, aiNoWallSetPar(index, 30));
                    aiDat[index].f82 = 180;
                }
            }
        } else {
            if (param == 0) {
                if (aiDat[index].fE4 == 0) {
                    if (zdAI_IsTurn(index) == 0) {
                        aiActSuspend_zoid(index);
                        zdAI_StopAngRun(index, aiNoWallSetPar(index, 20));
                        aiDat[index].f82 = 60;
                    }
                    return 1;
                }
            } else {
                aiDat[index].f82 = 60;
                if (zdAI_freeAng(index, (f32)Tea_aidat[index].f48)) {
                    zdAI_Run(index, 0);
                    aiDat[index].f82 = 60;
                    aiDat[index].f68 = 0;
                    return 1;
                }
            }
        }
        aiDat[index].f68 = 1;
        return 1;
    }
    return result;
}

s32 aiActSuspend_SquarelyEnemy(s16 index)
{
    s32 result = 0;
    s16 rnd;

    rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 360);
    if (aiDat[index].f58 == 0) {
        return 0;
    }
    if (aiDat[index].f3A > -150 && aiDat[index].f3A < 0) {
        return 0;
    }
    if (aiDat[index].f3A < 150 && aiDat[index].f3A > 0) {
        return 0;
    }
    if (aiDat[index].f88 == 0 && aiDat[index].f82 == 0 && aiDat[index].f7A <= 0 && aiDat[index].f54 == 0) {
        aiDat[index].f82 = 120;
        aiDat[index].f7A = 120;
        aiDat[index].fE8 = 60;
        result = 1;
        zdAI_Look(index);
        return 1;
    }
    return 0;
}

s32 aiActSuspend_ZoidStoped(s16 index)
{
    s32 result = 0;
    s32 rnd = (s32)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 120 + 120);
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;

    if (Tea_aidat[index].f38 == 1) {
        return 0;
    }
    if (aiDat[index].fDA > 300) {
        aiZoidJump(index);
    } else if (aiDat[index].fDA > 240) {
        aiZoidStep(index, 0);
    }
    if (aiDat[index].fDA > 300) {
        if (aiDat[index].f64 != 1) {
            zdAI_Run(index, 0);
        }
        aiDat[index].f82 = Tea_aidat[index].f5E;
        result = 1;
    }
    return result;
}

s32 aiActSuspend_EnemySupplement(s16 index)
{
    s32 result = 0;
    s32 mode = 0;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 360);

    result = result;
    result = result;
    result = result;
    result = result;
    mode = ((ZoidAIState3 *)Zoid[index].ai)->f90;
    if (mode == 0) {
        mode = 5;
    }
    if (aiDat[index].fC0 == 0) {
        return 0;
    }
    if (aiDontMove(index)) {
        return 0;
    }
    if (mode != 5) {
        aiActSuspend_zoid(index);
        switch (mode) {
        case 1:
            aiZoidRunMode(index, -1, 0, -1);
            aiWepAtck(index);
            break;
        case 2:
            aiZoidRunMode(index, -1, 0, -1);
            break;
        case 3:
            aiWepAtck(index);
            aiZoidRunMode(index, -1, 8, 140);
            aiWepAtck(index);
            break;
        case 4:
            if (aiDat[index].fD0 % 30 < 15) {
                aiZoidRunMode(index, -1, 0, -1);
            } else {
                aiZoidRunMode(index, -1, 7, -1);
            }
            break;
        }
        return 1;
    }
    if (Tea_aidat[index].fDC) {
        if (aiDat[index].fB6 < Tea_aidat[index].fE8) {
            zdAI_setHigh(index, 1);
        } else {
            zdAI_setHigh(index, 2);
        }
    }
    if (aiDat[index].fE4 != 0 && aiDat[index].fDE <= 0) {
        return 0;
    }
    if (Tea_aidat[index].f25) {
        aiActSuspend_zoid(index);
        aiZoidRunMode(index, -1, 0, -1);
        return 1;
    } else if (Tea_aidat[index].f27) {
        aiActSuspend_zoid(index);
        aiZoidRunMode(index, -1, 6, Tea_aidat[index].f28);
        return 1;
    } else if (Tea_aidat[index].f26) {
        aiActSuspend_zoid(index);
        aiZoidRunMode(index, -1, 5, -1);
        result = 1;
    }
    return result;
}

void aiWepAtck(s16 index)
{
    s16 id = 0;
    s16 slot = 0;
    s16 bullet = 0;
    s16 type = 0;
    s16 dist = 0;
    s32 flag = 0;

    slot = aiDat[index].fEA;
    id = zdAI_WeaponGetID(index);
    if (id >= 0) {
        bullet = Tea_partsdat[id].f5C;
    }
    if (bullet >= 0) {
        type = Tea_bulletdat[bullet].f12;
        if (Tea_bulletdat[bullet].f2A != 0) {
            flag = 1;
        }
    }
    if (flag == 0) {
        if ((s32)Tea_aidat[index].f01 == 1 && (type == 0 || type == 2) && (s32)Tea_aidat[index].fF3 == 1) {
            if (zdAI_IsFire(index)) {
                aiWepAtckFire(index);
            }
            return;
        }
        if (aiDat[index].f54 == 1) {
            if ((s32)Tea_aidat[index].f01 == 1 && type == 0) {
                aiWepAtckFire(index);
            }
            if ((s32)Tea_aidat[index].f01 == 1 && type == 2) {
                aiWepAtckFire(index);
            }
            if ((s32)Tea_aidat[index].f01 == 1 && type == 6 && zdAI_IsTarget(index)) {
                aiWepAtckFire(index);
            }
            if ((s32)Tea_aidat[index].f03 == 1 && (type == 1 || type == 5)) {
                aiWepAtckFire(index);
            }
        } else {
            if ((s32)Tea_aidat[index].f03 == 1 && (type == 1 || type == 5) && zdAI_IsTarget(index)) {
                aiWepAtckFire(index);
            }
            if ((s32)Tea_aidat[index].f01 == 1 && (type == 0 || type == 2) && zdAI_IsTarget(index)) {
                aiWepAtckFire(index);
            }
        }
    }
    if (aiDat[index].fE4 != 0 && type == 2 && flag == 1 && slot != -1) {
        dist = Zoid[index].field_1F48[slot];
        if (aiDat[index].fB6 >= Tea_aidat[index].fE4 && dist < Tea_aidat[index].fEA) {
            aiWepAtckFire(index);
        }
    }
}

void aiWepAtckFire(s32 index)
{
    s16 id = 0;
    s16 bullet = 0;
    s16 type = 0;

    id = zdAI_WeaponGetID(index);
    if (id >= 0) {
        bullet = Tea_partsdat[id].f5C;
    }
    if (bullet >= 0) {
        type = Tea_bulletdat[bullet].f12;
    }
    if (aiDat[index].f76 <= 0) {
        if (type == 1) {
            if (aiDat[index].f74 < 0) {
                aiDat[index].f74 = Tea_aidat[index].f54;
                zdAI_WeaponFire1(index);
            }
            if (aiDat[index].f74 > 0 && (s32)Tea_aidat[index].f04 == 1) {
                zdAI_WeaponFireON(index);
                zdAI_WeaponFire1(index);
            }
        } else {
            if (aiDat[index].f74 < 0) {
                aiDat[index].f74 = Tea_aidat[index].f54;
                zdAI_WeaponFire1(index);
            }
            if (aiDat[index].f74 > 0 && (s32)Tea_aidat[index].f02 == 1) {
                zdAI_WeaponFireON(index);
                zdAI_WeaponFire1(index);
            }
        }
    }
}

s32 aiNextWeapon(s32 index)
{
    s32 tries = 0;
    s32 bullet = 0;
    s32 ready = 1;

    if (aiDat[index].f78 > 0)
        return 0;
    for (tries = 0; tries < 28; tries++) {
        zdAI_WeaponChg(index);
        bullet = zdAI_WeaponBullet(index);
        if (bullet != 0)
            break;
    }
    if (bullet == 0)
        ready = 0;
    aiDat[index].f78 = 180;
    aiDat[index].f8C = ready;
    ready = ready;
    return ready;
}

void aiWepChange(s16 index)
{
    s16 old = 0;
    s32 flag = 0;
    s16 dist = 0;
    s16 id = 0;
    s16 bullet = 0;
    s16 type = 0;
    s8 sel = 0;

    old = aiDat[index].fEA;
    dist = dist;
    if (Tea_aidat[index].f64) {
        aiWepChangeManual(index);
        return;
    }
    if (aiDat[index].fE4 != 0) {
        if (old != -1) {
            dist = Zoid[index].field_1F48[old];
        } else {
            dist = 9999;
        }
        if (aiDat[index].f54 != 0 && aiDat[index].fB6 >= Tea_aidat[index].fE8 && aiDat[index].fB6 < Tea_aidat[index].fEC && zdAI_cmpHigh(index)) {
            sel = Tea_aidat[index].fE6;
            id = zdAI_WeaponSlotGetID(index, sel);
            if (id >= 0) {
                bullet = Tea_partsdat[id].f5C;
            }
            if (bullet >= 0) {
                type = Tea_bulletdat[bullet].f12;
                flag = 0;
                if (Tea_bulletdat[bullet].f2A != 0) {
                    flag = 1;
                }
            }
            if (type == 0 || type == 2 || flag == 0) {
                if (zdAI_WeaponSlotBullet(index, sel) <= 0) {
                    sel = aiWepSearchSlot(index, 0, 2);
                }
            } else {
                sel = aiWepSearchSlot(index, 0, 2);
            }
            if (sel != aiDat[index].fAE) {
                zdAI_WeaponChgSlot(index, sel);
                aiDat[index].f78 = Tea_aidat[index].f58;
                aiDat[index].fAE = sel;
                aiDat[index].f76 = 0;
            }
            if (zdAI_WeaponBullet(index) > 0) {
                return;
            }
        }
        if (aiDat[index].fB6 >= Tea_aidat[index].fE4 && dist < Tea_aidat[index].fEA) {
            sel = Tea_aidat[index].fE2;
            id = zdAI_WeaponSlotGetID(index, sel);
            if (id >= 0) {
                bullet = Tea_partsdat[id].f5C;
            }
            if (bullet >= 0) {
                type = Tea_bulletdat[bullet].f12;
                flag = 0;
                if (Tea_bulletdat[bullet].f2A != 0) {
                    flag = 1;
                }
            }
            if (type == 2 && flag == 1) {
                if (zdAI_WeaponSlotBullet(index, sel) <= 0) {
                    sel = aiWepSearchSlot(index, 2, 2);
                }
            } else {
                sel = aiWepSearchSlot(index, 2, 2);
            }
            if (sel != aiDat[index].fAE) {
                zdAI_WeaponChgSlot(index, sel);
                aiDat[index].f78 = Tea_aidat[index].f58;
                aiDat[index].fAE = sel;
                aiDat[index].f76 = 0;
            }
            if (zdAI_WeaponBullet(index) > 0) {
                return;
            }
        }
        if (aiDat[index].fB6 < Tea_aidat[index].fF0) {
            sel = Tea_aidat[index].fEE;
        } else {
            sel = Tea_aidat[index].fEF;
        }
        id = zdAI_WeaponSlotGetID(index, sel);
        if (id >= 0) {
            bullet = Tea_partsdat[id].f5C;
        }
        if (bullet >= 0) {
            type = Tea_bulletdat[bullet].f12;
        }
        if (type == 1 || type == 6) {
            if (zdAI_WeaponSlotBullet(index, sel) <= 0) {
                sel = aiWepSearchSlot(index, 1, 6);
            }
        } else {
            sel = aiWepSearchSlot(index, 1, 6);
        }
        if (sel != aiDat[index].fAE) {
            zdAI_WeaponChgSlot(index, sel);
            aiDat[index].f78 = Tea_aidat[index].f58;
            aiDat[index].fAE = sel;
            aiDat[index].f76 = 0;
        }
        if (zdAI_WeaponBullet(index) > 0) {
            return;
        }
        sel = aiNextWeaponScan(index);
        if (sel != -1 && sel != aiDat[index].fAE) {
            aiDat[index].f78 = Tea_aidat[index].f58;
            aiDat[index].fAE = sel;
            aiDat[index].f76 = 0;
        }
    } else {
        aiNextWeapon(index);
        aiDat[index].f78 = Tea_aidat[index].f58;
        aiDat[index].f76 = 0;
    }
}

void aiWepChangeManual(s16 index)
{
    s16 i = 0;
    s16 best = 0;
    s16 cnt = 0;
    s16 chosen = -1;
    s16 old = aiDat[index].fD0;

    best = 0;
    cnt = 0;
    for (i = 1; i < 10; i++) {
        cnt++;
        if (Tea_aidat[index].f66[i] == 0) {
            break;
        }
    }
    best = -1;
    for (i = 0; i < cnt; i++) {
        if (old >= Tea_aidat[index].f66[i]) {
            best = i;
        }
    }
    if (best == -1 || best == cnt - 1) {
        aiDat[index].fCC = OSGetTime() / (__OSBusClock / 4);
        aiDat[index].fD0 = OSGetTime() / (__OSBusClock / 4) - aiDat[index].fCC;
        aiDat[index].fD0 = 0;
        best = 0;
    }
    if (aiDat[index].fC0 == 1) {
        if (aiDat[index].fB6 < Tea_aidat[index].f7A[best]) {
            chosen = Tea_aidat[index].fA2[best];
        } else {
            chosen = Tea_aidat[index].fB6[best];
        }
    } else {
        chosen = Tea_aidat[index].fB6[best];
    }
    if (chosen != aiDat[index].fAE) {
        zdAI_WeaponChgSlot(index, chosen);
        aiDat[index].f78 = Tea_aidat[index].f58;
        aiDat[index].fAE = chosen;
        aiDat[index].f76 = 0;
    }
}

void aiGrapAtck(s16 index)
{
    s16 a = 0;
    s16 b = 0;
    s16 c = 0;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 51);
    s32 d = 0;

    if (Tea_aidat[index].f00 != 0 && aiDat[index].f64 != 1 && aiDat[index].f54 != 0 && zdAI_IsAtack(index) && aiDat[index].f80 <= 0) {
        if (aiDat[index].f7E < 0) {
            aiDat[index].f7E = Tea_aidat[index].f4C;
        }
        if (aiDat[index].fE4 == 0) {
            if (rnd >= Tea_aidat[index].f2A / 2) {
                aiZoidJump(index);
            }
        } else {
            if (Tea_aidat[index].f09 == 0) {
                if (rnd >= (100 - Tea_aidat[index].f07) / 2) {
                    return;
                }
                if (rnd >= Tea_aidat[index].f2A / 2) {
                    return;
                }
            }
        }
        zdAI_Atack1(index);
    }
}

s32 aiActSuspend_ObstacleFlight(s16 index, s16 param)
{
    s32 result = 0;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 360);
    s16 copy = param;
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;

    if (aiDontMove(index)) {
        return 0;
    }
    if (aiDat[index].f68 == 1) {
        if (aiDat[index].f60 == 0) {
            aiDat[index].f68 = 0;
            aiActFlightZoidLow(index);
            return 0;
        } else if (aiDat[index].f82 == 0) {
            aiActFlightZoidHigh(index);
        }
    } else if (aiDat[index].f60 == 0) {
        aiDat[index].f68 = 0;
    }
    if (aiDat[index].f60 == 1) {
        aiActFlightZoidHigh(index);
        if (zdAI_coHead(index)) {
            if (zdAI_IsTurn(index) == 0) {
                aiActSuspend_zoid(index);
                zdAI_StopAngRun(index, aiNoWallSetPar(index, 45));
                aiDat[index].f82 = 120;
                aiDat[index].f30 = 120;
                aiDat[index].f68 = 1;
                return 1;
            } else {
                aiActFlightZoidHigh(index);
                zdAI_Step(index, 90);
                return 0;
            }
        } else {
            aiActFlightZoidHigh(index);
            aiActSuspend_zoid(index);
            zdAI_Run(index, aiNoWallSetPar(index, 45));
            aiDat[index].f68 = 1;
            return 0;
        }
    } else if (zdAI_coHead(index)) {
        zdAI_Run(index, aiNoWallSetPar(index, 45));
        aiActFlightZoidHigh(index);
        zdAI_Step(index, 90);
        return 1;
    }
    return result;
}

void aiFlightProc(s32 index)
{
    s32 a = 0;
    s32 dead = 0;
    s32 flag = 1;
    s32 b = 0;
    s16 rnd = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 100);
    ZoidState *zoid;
    ZoidAIState3 *ai;

    flag = flag;
    flag = flag;
    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0) {
            ai = (ZoidAIState3 *)zoid->ai;
            if (aiDat[index].f78 == 0) {
                aiWepChange(index);
            }
            if (aiDat[index].f76 == 0) {
                aiWepAtck(index);
            }
            aiGrapAtck(index);
            aiTargetFinalDestinationMode(index);
            if (aiDat[index].fD6 > 0) {
                aiDat[index].fD6--;
            }
            if (aiDat[index].fD6 == 0) {
                aiDat[index].fD6 = -1;
                aiDat[index].fD8 = 0;
                aiDat[index].fB8 = 0;
                aiZoidRun_ResetCommand(index);
            }
            aiActSuspend_ObstacleFlight(index, zoid->speed);
            aiActSuspend_FarWepStep(index);
            if (aiTerritoryCheck(index) == 1) {
                return;
            }
            flag = 1;
            aiActOrbitChk(index);
            if (index == 2) {
                if (aiActSuspend_Partner(ai->f90, ai->f74)) {
                    return;
                }
            }
            dead = 1;
            flag = aiActSuspend_EnemySupplement(index);
            switch (aiDat[index].fEC) {
            case 0:
                if (aiActSuspend_SquarelyPerson(index, zoid->target_slot)) {
                    (void)0;
                }
                aiDat[index].fEC++;
                break;
            case 1:
                aiActSuspend_FarWep(index);
                aiDat[index].fEC++;
                break;
            case 2:
                if (aiActSuspend_EnemyAtck(index) == 1) {
                    (void)0;
                }
                aiDat[index].fEC++;
                break;
            case 3:
                aiDat[index].fEC++;
                break;
            case 4:
                if (0.0f == zoid->speed) {
                    aiDontMove(index);
                }
                aiDat[index].fEC++;
                break;
            case 5:
                if (zdAI_WarningArea(index) == 1 && aiDat[index].f30 <= 0) {
                    aiActSuspend_zoid(index);
                    if (aiDat[index].fC0 != 0) {
                        zdAI_SetLenIn(index, 10.0f);
                        if (aiDat[index].f76 == 0) {
                            aiWepAtck(index);
                        }
                    } else {
                        aiZoidRun(index);
                        zdAI_goPoint(index, 0.0f, 0.0f);
                    }
                    aiDat[index].f82 = 120;
                    aiDat[index].f30 = 120;
                    aiDat[index].f84 = 120;
                }
                aiDat[index].fEC++;
                break;
            default:
                if (flag == 0) {
                    aiZoidRun(index);
                }
                aiDat[index].fEC = 0;
                break;
            }
        }
    }
}

void aiZoidRun_ResetCommand(s16 index)
{
    s16 rnd1 = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 20 + 90);
    s16 zero = 0;
    s16 copy = index;
    s16 motion = 0;
    s32 p1 = 0;
    s32 p2 = 0;
    s16 len = 0;
    s16 rnd2 = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 110);
    s16 unused = 0; (void)unused;
    f32 scale = (f32)((((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 40 + 80) / 100);
    s16 rx = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 3000 - 1500);
    s16 rz = (s16)(((OSGetTime() * 8) / ((__OSBusClock / 4) / 125000)) % 6251 / 2 - 1500);
    s16 slot = 0;
    s16 count = 0;
    s16 ang = 0;
    s16 dir = 0;

    if ((s32)(s8)Tea_aidat[index].f2B == 1) {
        aiDat[index].f14 = 0;
        p1 = rnd1 * Tea_aidat[index].f30;
        ang = p1 / 100;
        p2 = rnd1 * Tea_aidat[index].f2E;
        len = p2 / 100;
        switch (aiDat[index].fC8) {
        case 0:
            zdAI_Run(index, 0);
            aiDat[index].fC8 = 1;
            aiDat[index].fB8 = scale * Tea_aidat[index].f32;
            break;
        case 1:
            zdAI_RunAng(index, ang);
            if (rnd2 < 100 - (Tea_aidat[index].f2A + 10)) {
                aiDat[index].fC8 = 2;
            }
            aiDat[index].fB8 = len;
            break;
        case 2:
            zdAI_Run(index, 0);
            aiDat[index].fC8 = 3;
            aiDat[index].fB8 = scale * Tea_aidat[index].f32;
            break;
        case 3:
            zdAI_RunAng(index, -ang);
            if (rnd2 < 100 - (Tea_aidat[index].f2A + 10)) {
                aiDat[index].fC8 = 0;
            }
            aiDat[index].fB8 = len;
            break;
        case 4:
            aiDat[index].fC8 = 0;
            zdAI_goPoint(index, rx, rz);
            aiDat[index].fB8 = len;
        default:
            aiDat[index].fC8 = 0;
            aiDat[index].fB8 = 0;
            break;
        }
    } else {
        if ((s32)(s8)Tea_aidat[index].f34 == 1) {
            if (aiDat[index].fC0 == 1) {
                return;
            }
            aiDat[index].f14 = 1;
            len = Tea_relaydat[index].b1;
            count = Tea_relaydat[index].b0;
            if (aiDat[index].fAA == -1) {
                aiDat[index].fAA = slot = 0;
                if (Tea_relaydat[index].b0 > 1) {
                    aiDat[index].fAC = 1;
                } else {
                    aiDat[index].fAC = -1;
                    if ((s32)(s8)Tea_relaydat[index].b1 == 1) {
                        aiDat[index].fAC = 0;
                    }
                }
                zdAI_goPoint(index, Tea_relaydat[index].f02[slot], Tea_relaydat[index].f2A[slot]);
                aiDat[index].fBC = 0;
            } else {
                if (aiDat[index].fAA == aiDat[index].fAC || aiDat[index].fAC == -1) {
                    if (aiDat[index].fAC == -1) {
                        if ((s32)(s8)Tea_relaydat[index].b1 == 1) {
                            aiDat[index].fAC = 0;
                        }
                    } else {
                        aiDat[index].fAC++;
                        if (aiDat[index].fAC > count) {
                            if ((s32)(s8)Tea_relaydat[index].b1 == 1) {
                                aiDat[index].fAC = 0;
                            } else {
                                aiDat[index].fAC = -1;
                            }
                        }
                    }
                }
                if (aiDat[index].fBC == 1) {
                    slot = aiDat[index].fAC;
                    if (slot != -1) {
                        aiDat[index].fAA = slot;
                        zdAI_goPoint(index, Tea_relaydat[index].f02[slot], Tea_relaydat[index].f2A[slot]);
                        aiDat[index].fAA = aiDat[index].fAC;
                        aiDat[index].fAC++;
                        slot = aiDat[index].fAC;
                        if (slot > count || slot == -1) {
                            if ((s32)(s8)Tea_relaydat[index].b1 == 1) {
                                aiDat[index].fAC = 0;
                            } else {
                                aiDat[index].fAC = -1;
                            }
                        }
                        aiDat[index].fBC = 0;
                    } else {
                        if ((s32)(s8)Tea_relaydat[index].b1 == 1) {
                            aiDat[index].fAC = 0;
                        }
                    }
                } else {
                    slot = aiDat[index].fAA;
                    zdAI_goPoint(index, Tea_relaydat[index].f02[slot], Tea_relaydat[index].f2A[slot]);
                }
            }
        }
        if ((s32)(s8)Tea_aidat[index].f38 == 1) {
            aiDat[index].f14 = 2;
            if (Tea_aidat[index].f05 == 0) {
                dir = 20;
            } else {
                dir = -20;
            }
            if (Tea_aidat[index].f3A == 0) {
                if (!aiZoidRunTargetAttain(index)) {
                    zdAI_goPoint(index, Tea_aidat[index].f3C, Tea_aidat[index].f3E);
                }
            } else {
                zdAI_rotPoint(index, Tea_aidat[index].f3C, Tea_aidat[index].f3E, Tea_aidat[index].f3A, dir);
            }
        }
        if ((s32)(s8)Tea_aidat[index].f40 == 1) {
            aiDat[index].f14 = 3;
            motion = Tea_aidat[index].f42;
            if (!aiZoidRunTargetAttain(index)) {
                zdAI_goPoint(index, Tea_aidat[index].f3C, Tea_aidat[index].f3E);
            } else {
                zdAI_WaitMotion(index, motion);
            }
        }
    }
}

s32 aiZoidRunTargetAttain(s16 index)
{
    f32 dist = 0.0f;
    f32 x = 0.0f;
    f32 z = 0.0f;
    s16 d = 0;
    s16 slot = 0;

    if ((s32)Tea_aidat[index].f34 != 1) {
        return 0;
    }
    slot = aiDat[index].fAA;
    if (slot == -1) {
        return 0;
    }
    x = (f32)Tea_relaydat[index].f02[slot];
    z = (f32)Tea_relaydat[index].f2A[slot];
    dist = zdAI_lenPoint(index, x, z);
    d = dist;
    aiDat[index].fCA = d;
    if (aiDat[index].fCA <= 20) {
        /* MWCC deletes these high words after allocation, then schedules the block again. */
        if (aiDat[index].fBC == 0 &&
            ((void)((s64)(s32)Tea_relaydat),
             (void)((s64)(s32)Tea_relaydat),
             (void)((s64)(s32)Tea_relaydat),
             (void)((s64)(s32)Tea_relaydat),
             (void)((s64)(s32)Tea_relaydat),
             (void)((s64)(s32)Tea_relaydat),
             (void)((s64)(s32)Tea_relaydat),
             Tea_relaydat[(s32)index].f52[slot]) != 0) {
            zdAI_WaitMotion(index, Tea_relaydat[index].f7A[slot]);
            aiDat[index].f84 = Tea_relaydat[index].fA2[slot];
        }
        aiDat[index].fBC = 1;
        return 1;
    }
    return 0;
}

}
