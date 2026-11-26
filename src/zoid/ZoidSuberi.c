#pragma readonly_strings on
#include "zoid3.h"

extern f32 cosf(f32 angle);
extern f32 sinf(f32 angle);
extern void dummyFunc(const char *);
extern s32 sCamNN;

void ZoidSuberi(ZoidState *zoid)
{
    f32 speed;
    f32 a;
    f32 b;
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        dummyFunc("Sube>");
        if (sCamNN == 4) {
            return;
        }
        zoid->slide_frames++;
        speed = zoid->slide_speed;
        if (speed == 0.0f) {
            zoid->slide_frames = 0;
            return;
        }
        if (zoid->slide_frames < 15) {
            return;
        }
        a = -zoid->heading;
        zoid->position[0] -= 1.5 * (zoid->slide_speed * cosf(a));
        b = -zoid->heading;
        zoid->position[2] -= 1.5 * (zoid->slide_speed * sinf(b));
    }
}
