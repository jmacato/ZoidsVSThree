#include "types.h"

extern u64 OSGetTime(void);
extern void draw1(s32 first_camera);
extern s32 sCamNN;
extern u8 sCamera[];
extern void *camTmp;
extern s32 drawTime;

void drawAll(void)
{
    u64 start = OSGetTime();
    s32 i;

    for (i = 0; i < 4; i++) {
        camTmp = sCamera + i * 0x590;
        draw1(i != sCamNN - 1);
    }
    drawTime = OSGetTime() - start;
}
