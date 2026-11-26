#include "zoid3.h"

extern void ZoidPurge(ZoidState *zoid);

void ZoidPurgeAll(void)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        ZoidPurge(&Zoid[i]);
    }
}
