#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern f32 sMisZd(ZoidState *zoid);

f32 zdAI_ComeMissile(s32 index)
{
    ZoidState *zoid;
    f32 result;

    aiCmdReport("aiCmd-comeMissile \n");
    result = -1.0f;
    if (index < 0) {
        return result;
    }
    if (index >= 16) {
        return result;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return result;
    }
    return sMisZd(zoid);
}
