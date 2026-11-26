#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern s32 sWeaponGetMountBullet(ZoidState *zoid, s32 index);

s32 zdAI_WeaponSlotBullet(s32 index, s32 slot)
{
    ZoidState *zoid;

    aiCmdReport("aiCmd-wpSlotBullet \n");
    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    zoid = &Zoid[index];
    return sWeaponGetMountBullet(zoid, slot);
}
