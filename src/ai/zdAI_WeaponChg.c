#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void zdWeaponChg(ZoidState *zoid);

void zdAI_WeaponChg(s32 index)
{
    aiCmdReport("aiCmd wpChg \n");
    if (index >= 0 && index < 16) {
        zdWeaponChg(&Zoid[index]);
    }
}
