#include "zoid3.h"

extern s32 gameStartTm;
extern s32 gameStartF;
extern u8 sCamera[];
extern void zdLinierTm(ZoidState *zoid, s32 frames);
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);
extern void ZoidSearchNextTarget(ZoidState *zoid);

void gameStartZoid(void)
{
    s32 i;
    ZoidState *zoid;

    gameStartTm = 0;
    gameStartF = 0;
    for (i = 0; i < 4; i++) {
        if (*(void **)(sCamera + i * 0x590 + 0x244) != 0) {
            zoid = *(ZoidState **)(sCamera + i * 0x590 + 0x1C4);
            if (zoid != 0 && zoid->joint != 0) {
                zdLinierTm(zoid, 0x78);
                ZoidSetAnim(zoid, 1);
                zdLinierTm(zoid, 0x78);
                zoid->action = 0;
                zoid->requested_action = 0;
                ZoidSearchNextTarget(zoid);
            }
        }
    }
}
