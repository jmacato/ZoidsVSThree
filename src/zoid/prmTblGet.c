#include "zoid3.h"

typedef struct PrmTblEntry {
    u8 pad_0000[0x750];
} PrmTblEntry;

extern s32 prmTblN;
extern PrmTblEntry prmTblParam[4];
extern s32 prmTblSearch(s32 value);
extern void prmTblSet(s32 index, s32 value);

void *prmTblGet(s32 value)
{
    s32 index;

    if (value < 0) {
        return 0;
    }
    if (value >= 300) {
        return 0;
    }
    index = prmTblSearch(value);
    if (index == -1) {
        prmTblN = prmTblN + 1;
        if (prmTblN >= 4) {
            prmTblN = 0;
        }
        index = prmTblN;
        prmTblSet(index, value);
    }
    return &prmTblParam[index];
}
