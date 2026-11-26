#include "zoid3.h"

extern void zdWp1Slider(ZoidState *zoid, s32 slot, s32 on);
extern void zdWeaponForceFireOnOff_(ZoidState *zoid, s32 mount, s32 on);

void zdOptionUseOnOff2(ZoidState *zoid, s32 on)
{
    zoid->booster_on = on;
    zdWp1Slider(zoid, 0xC, on);
    zdWeaponForceFireOnOff_(zoid, WEAPON_MOUNT_BOOSTER, on);
}
