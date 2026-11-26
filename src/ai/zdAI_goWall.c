#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern s32 chkBossArea(ZoidState *zoid);
extern s32 zdFaceAtk(ZoidState *zoid, f32 distance, f32 degrees);

s32 zdAI_goWall(s32 index, s32 distance, s32 degrees)
{
    ZoidState *zoid;

    aiCmdReport("aiCmd-goWall \n");
    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return 0;
    }
    if (chkBossArea(zoid)) {
        return 1;
    }
    return zdFaceAtk(zoid, (f32)distance, (f32)(2.0 * (3.1415926 * (f32)degrees) / 360.0));
}
