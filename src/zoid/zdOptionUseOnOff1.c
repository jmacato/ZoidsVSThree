#include "zoid3.h"

extern void zdWeaponForceFireOnOff_(ZoidState *zoid, s32 mount, s32 on);
extern void zdWp1Slider(ZoidState *zoid, s32 arg, s32 on);

void zdOptionUseOnOff1(ZoidState *zoid, s32 on)
{
    zdWp1Slider(zoid, 0xb, on);
    zdWeaponForceFireOnOff_(zoid, WEAPON_MOUNT_SHIELD, on);
}
