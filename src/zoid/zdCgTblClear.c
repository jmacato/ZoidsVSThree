#include "zoid3.h"

void zdCgTblClear(ZoidState *zoid)
{
    s32 i;

    for (i = 0; i < 0x2000; i++) {
        zoid->cg_table[i] = 0;
    }
    zoid->field_40FC = 0;
}
