#include "zoid.h"

extern s32 sWeaponGetAnim(s32 weapon);
extern void sWeaponSetAnim(s32 weapon, s32 animation);
extern void sWeaponLoopOFF(s32 weapon);
extern void sWeaponStopOFF(s32 weapon);

void zdWeaponForceFire1_(ZoidState *zoid, s32 selected);

void zdOptionUse4(ZoidState *zoid)
{
    zdWeaponForceFire1_(zoid, WEAPON_MOUNT_SMOKE_MINE);
}

void zdOptionUse5(ZoidState *zoid)
{
    zdWeaponForceFire1_(zoid, WEAPON_MOUNT_SMOKE_MINE);
}
