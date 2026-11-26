#include "zoid3.h"

typedef struct FlyLimbs {
    u8 pad_0000[0x4C];
    ZoidLimb limbs[9];
} FlyLimbs;

extern s32 sCamNN;
extern s32 gameStartTm;
extern void ZoidTo(ZoidState *zoid, ZoidLimb *limb, s32 flag);
extern void ZoidToF(ZoidLimb *limb, ZoidLimb *target, f32 rate);
extern void ZoidToDownF(ZoidLimb *limb, ZoidLimb *target, f32 rate);

void ZoidToFly(ZoidState *zoid)
{
    s32 flag;
    f32 rate;
    s32 i;

    if (sCamNN == 4) {
        return;
    }
    flag = 0;
    rate = 0.1f;
    if (zoid->action >= 0xD && zoid->action <= 0x16) {
        flag = 1;
    }
    if (flag != 0) {
        rate = 1.0f;
    }
    if (gameStartTm < 4 && zoid->action == 0x32) {
        rate = 1.0f;
    }
    ZoidTo(zoid, &((FlyLimbs *)zoid)->limbs[8], flag);
    if (zoid->death_pending != 0) {
        ZoidToDownF(&((FlyLimbs *)zoid)->limbs[1], &((FlyLimbs *)zoid)->limbs[8], rate);
    } else {
        ZoidToF(&((FlyLimbs *)zoid)->limbs[1], &((FlyLimbs *)zoid)->limbs[8], rate);
    }
    for (i = 2; i < 8; i++) {
        if (zoid->death_pending != 0) {
            ZoidToDownF(&((FlyLimbs *)zoid)->limbs[i], &((FlyLimbs *)zoid)->limbs[i - 1], rate);
        } else {
            ZoidToF(&((FlyLimbs *)zoid)->limbs[i], &((FlyLimbs *)zoid)->limbs[i - 1], rate);
        }
    }
}
