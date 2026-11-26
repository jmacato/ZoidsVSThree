#include "types.h"

typedef struct Param {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 arr10[8];
    s32 f30[2];
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    u8 pad_54[0x98 - 0x54];
    s32 f98;
    s32 f9C;
    s32 fA0;
    s32 fA4;
    s32 fA8;
    s32 fAC;
    s32 fB0;
    s32 fB4;
    s32 fB8;
    s32 fBC;
    s32 fC0;
    s32 fC4;
    s32 fC8;
    s32 fCC;
    s32 fD0;
    u8 pad_D4[0xE8 - 0xD4];
    f32 fE8;
    f32 fEC;
    f32 fF0;
    s32 fF4;
    u8 pad_F8[0xFC - 0xF8];
    s32 fFC;
    u8 pad_100[0x190 - 0x100];
    s32 f190;
} Param;

void paramInit(Param *p)
{
    s32 i;

    p->f00 = 1;
    p->f04 = 1;
    p->f08 = 2;
    p->f0C = 2;
    for (i = 0; i < 8; i++) {
        p->arr10[i] = 1;
    }
    p->f38 = 1;
    p->f40 = 1;
    p->f48 = 1;
    p->f50 = 1;
    p->f98 = 0;
    p->fA0 = 10;
    p->fA4 = 15;
    p->fE8 = 0.0f;
    p->fF0 = 25.0f;
    p->fEC = 7.0f;
    p->f9C = 0x78;
    p->fA8 = 9;
    p->fAC = 0x28;
    p->fB0 = 10;
    p->fB4 = 0x1F;
    p->fB8 = 0x12;
    p->fBC = 0x47;
    p->fC0 = 12;
    p->fC4 = 0x190;
    p->fF4 = 4;
    p->fC8 = 0x28;
    p->fCC = 0x14;
    p->fFC = 3;
    p->fD0 = 0x28;
    p->f190 = 4;
}
