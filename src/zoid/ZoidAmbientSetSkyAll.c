#include "zoid3.h"

extern void zdAmbientSetSky(ZoidState *zoid);

void ZoidAmbientSetSkyAll(void)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        zdAmbientSetSky(&Zoid[i]);
    }
}
