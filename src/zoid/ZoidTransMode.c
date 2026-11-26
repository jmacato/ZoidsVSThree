#include "zoid3.h"

extern void zdStelON(ZoidState *zoid);
extern void zdStelOFF(ZoidState *zoid);
extern void zdTrans1(ZoidState *zoid);
extern void zdSetMatStelOFF(ZoidState *zoid);
extern void zdSetMatStel(ZoidState *zoid);
extern void ZoidTrans(ZoidState *zoid, f32 transformation);
extern void ZoidCopyMatRet(ZoidState *zoid);

void ZoidTransMode(void)
{
    ZoidState *zoid;
    s32 i;

    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != (void *)0) {
            s32 state;
            s32 previous;

            if (zoid->option_active != 0) {
                zdStelON(zoid);
            } else {
                zdStelOFF(zoid);
            }
            state = zoid->stel_state;
            previous = zoid->previous_stel_state;
            if (previous == state) {
                if (state == ZOID_STEL_FADING) {
                    zdTrans1(zoid);
                }
            } else {
                if (previous == ZOID_STEL_ON) {
                    zdSetMatStelOFF(zoid);
                }
                if (previous == ZOID_STEL_FADING) {
                    ZoidTrans(zoid, 1.0f);
                }
                ZoidCopyMatRet(zoid);
                if (state == ZOID_STEL_FADING) {
                    zdTrans1(zoid);
                }
                if (state == ZOID_STEL_ON) {
                    zdSetMatStel(zoid);
                }
                zoid->previous_stel_state = state;
            }
        }
    }
}
