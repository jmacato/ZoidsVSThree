#include "zoid3.h"

extern void zdVoiceScript(ZoidState *zoid);

void ZoidVoiceScript(void)
{
    s32 i;
    ZoidState *zoid;
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != 0)
            zdVoiceScript(zoid);
    }
}
