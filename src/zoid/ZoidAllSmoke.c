#include "zoid3.h"

extern void zdSmoke(ZoidState *zoid);

void ZoidAllSmoke(void)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        zdSmoke(&Zoid[i]);
    }
}
