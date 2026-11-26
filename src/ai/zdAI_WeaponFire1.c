#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void zdWeaponFire1(ZoidState *zoid);

void zdAI_WeaponFire1(s32 index)
{
    aiCmdReport("aiCmd-wpFire \n");
    if (index >= 0 && index < 16) {
        zdWeaponFire1(&Zoid[index]);
    }
}
