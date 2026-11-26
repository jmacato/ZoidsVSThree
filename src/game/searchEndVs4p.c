#include "types.h"

extern s32 sortEndVs4p(void);
extern s32 calcEndVs4p(void);
extern s32 bp4pNm[10];

s32 searchEndVs4p(void)
{
    u8 unused[0xB8];
    s32 sorted;
    s32 result;
    s32 i;

    sorted = sortEndVs4p();
    result = calcEndVs4p();
    if (result != 0x63 && result != 0) {
        return result - 1;
    }
    if (sorted != 1) {
        return -1;
    }
    for (i = 0; i < 10; i++) {
        if (bp4pNm[i] == 1) {
            break;
        }
    }
    if (i == 10) {
        return -1;
    }
    return i;
}
