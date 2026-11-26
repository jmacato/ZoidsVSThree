#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern s32 sWeaponGetNumber(ZoidState *zoid, s32 selected);

s32 zdAI_WeaponSlotGetID(s32 index, s32 slot)
{
    ZoidState *zoid;

    aiCmdReport("aiCmd-weaponSlotGetID \n");
    if (index < 0) {
        return -1;
    }
    if (index >= 16) {
        return -1;
    }
    zoid = &Zoid[index];
    if (zoid->joint == (void *)0) {
        return -1;
    }
    return sWeaponGetNumber(zoid, slot);
}
