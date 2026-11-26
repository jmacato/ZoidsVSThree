#include "zoid3.h"

extern void zdCalc(ZoidState *zoid);

void ZoidCalcAll(void)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        zdCalc(&Zoid[i]);
    }
}
