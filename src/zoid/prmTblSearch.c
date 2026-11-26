#include "types.h"

extern s32 prmTblZ[4];

s32 prmTblSearch(s32 value)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        if (value == prmTblZ[i]) {
            return i;
        }
    }
    return -1;
}
