#include "types.h"
#include "game_mode.h"

extern void MemCpy(void *dst, const void *src, u32 size);
extern void OSReport(const char *format, ...);
extern s32 *fixSt;
extern s32 *fix;
extern u8 IveSaveFlag[];
extern u8 IveSave[];

void fixPut(void)
{
    s32 size;
    s32 total;
    s32 sum;
    u8 *base;

    size = 0x50;
    total = 0;
    total += size;
    fix = fixSt;
    MemCpy(&GameMode, (u8 *)fix + 8, 0x50);
    size = 0x1CB0;
    total += size;
    MemCpy(IveSaveFlag, (u8 *)fix + 0x58, 0x1CB0);
    total += size;
    MemCpy(IveSave, (u8 *)fix + 0x1D08, 0x1CB0);
    total += size;
    MemCpy(IveSave + 0x1CB0, (u8 *)fix + 0x39B8, 0x1CB0);
    total += size;
    MemCpy(IveSave + 0x72C0, (u8 *)fix + 0x5668, 0x1CB0);
    fix[1] = total;
    if ((u32)total >= 0x7318) {
        OSReport("StFixTbl size=%d tbl=%d \n", 0x7318, total);
    }
    size = 0;
    sum = 0;
    base = (u8 *)fix + 4;
    for (; size < total; size++) {
        sum += base[size];
    }
    fix[0] = sum;
}
