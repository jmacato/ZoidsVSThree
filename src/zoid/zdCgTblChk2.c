#include "zoid3.h"

extern u32 bitTBL[];

u32 zdCgTblChk2(u8 *table, u16 index)
{
    u8 mask = bitTBL[index & 7];
    u8 *cell = table + 0x20fc + index / 8;
    u8 hit = *cell & mask;
    *cell |= mask;
    return hit;
}
