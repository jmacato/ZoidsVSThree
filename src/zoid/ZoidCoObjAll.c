#include "zoid3.h"

extern void ZoidCoObjMtxI(ZoidState *zoid);
extern void sMissileZoid(void);

void ZoidCoObjAll(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        ZoidCoObjMtxI(&Zoid[i]);
    }
    for (i = 0; i < 16; i++) {
    }
    sMissileZoid();
}
