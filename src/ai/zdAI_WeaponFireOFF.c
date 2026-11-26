#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void zdWeaponFireOFF(ZoidState *zoid);

void zdAI_WeaponFireOFF(s32 index)
{
    aiCmdReport("aiCmd-wpFireOff \n");
    if (index >= 0 && index < 16) {
        zdWeaponFireOFF(&Zoid[index]);
    }
}
