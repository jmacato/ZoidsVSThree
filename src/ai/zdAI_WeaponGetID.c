#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern s32 sWeaponGetNumber(ZoidState *zoid, s32 mount);

s32 zdAI_WeaponGetID(s32 index)
{
    ZoidState *zoid;
    s32 mount;

    aiCmdReport("aiCmd-weaponGetID \n");
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
    mount = zoid->weapon_mount;
    return sWeaponGetNumber(zoid, mount);
}
