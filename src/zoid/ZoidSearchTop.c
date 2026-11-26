#include "zoid3.h"

extern void zdSearchTop(ZoidState *zoid);

void ZoidSearchTop(void)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        zdSearchTop(&Zoid[i]);
    }
}
