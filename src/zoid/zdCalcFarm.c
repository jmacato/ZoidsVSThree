#include "zoid3.h"

extern u8 IveSave[];
extern void zdCalcPre(ZoidState *zoid);
extern void zdCalcWeaponS(ZoidState *zoid, s32 index);
extern void zdCalcMan(ZoidState *zoid, s32 index);
extern void zdCalcEpi(ZoidState *zoid);

s32 zdCalcFarm(ZoidState *zoid, s32 slot, s32 a, s32 b)
{
    u8 *base;
    s32 index;
    s32 i;
    s32 w;

    if (zoid == 0)
        return 0;
    if (slot < 0)
        return 0;
    if (slot >= 4)
        slot = 0;
    base = IveSave + slot * 0x1cb0;
    index = *(s16 *)(base + 0x15f6);
    if (a != -1)
        index = a;
    if (b == -2)
        b = *(s16 *)(base + 0x1600);
    if (b == -3) {
        b = b;
    }
    if (index < 0)
        index = 0;
    zoid->type = *(s16 *)(base + 4 + index * 2);
    zdCalcPre(zoid);
    for (i = 0; i < 10; i++) {
        w = *(s16 *)(base + 0xb0e + index * 0x38 + i * 2);
        if (w != -1)
            zdCalcWeaponS(zoid, w);
    }
    for (i = 0; i < 3; i++) {
        w = *(s16 *)(base + 0x11da + index * 6 + i * 2);
        if (w != -1)
            zdCalcWeaponS(zoid, w);
    }
    if (*(s16 *)(base + 0x119e + index * 2) > 0)
        zdCalcWeaponS(zoid, *(s16 *)(base + 0x119e + index * 2));
    zdCalcMan(zoid, -1);
    zdCalcEpi(zoid);
    return index;
}
