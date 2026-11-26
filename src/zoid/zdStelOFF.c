#include "zoid3.h"

extern void ZoidTrans(ZoidState *zoid, f32 transformation);

void zdStelOFF(ZoidState *zoid)
{
    s32 state;
    f32 t;

    if (zoid == (void *)0) {
        return;
    }
    if (zoid->joint == (void *)0) {
        return;
    }
    state = zoid->stel_state;
    if (state == ZOID_STEL_ON) {
        ZoidTrans(zoid, 0.0f);
        zoid->stel_state = ZOID_STEL_FADING;
    } else if (state == ZOID_STEL_FADING) {
        t = zoid->transformation;
        t += 0.02;
        if (t > 1.0) {
            t = 1.0f;
            zoid->stel_state = ZOID_STEL_OFF;
        }
        ZoidTrans(zoid, t);
    }
}
