#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void zdWeaponFireON(ZoidState *zoid);

void zdAI_WeaponFireON(s32 index)
{
    aiCmdReport("aiCmd-wpFireOn \n");
    if (index >= 0 && index < 16) {
        zdWeaponFireON(&Zoid[index]);
    }
}
