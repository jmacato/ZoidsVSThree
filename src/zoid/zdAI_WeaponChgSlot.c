#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void zdWeaponChgSlot(ZoidState *zoid, s32 slot);

void zdAI_WeaponChgSlot(s32 index, s32 slot)
{
    aiCmdReport("aiCmd-wapCghSlot \n");
    if (index >= 0 && index < 16 && slot <= 9) {
        zdWeaponChgSlot(&Zoid[index], slot);
    }
}
