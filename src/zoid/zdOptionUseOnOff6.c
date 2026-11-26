#include "zoid3.h"

extern void zdWp1Slider(ZoidState *zoid, s32 slot, s32 on);
extern void zdWeaponForceFireOnOff_(ZoidState *zoid, s32 mount, s32 on);

void zdOptionUseOnOff6(ZoidState *zoid, s32 on)
{
    zoid->field_016C = on;
    zdWp1Slider(zoid, 0x10, on);
    zdWeaponForceFireOnOff_(zoid, WEAPON_MOUNT_BOOSTER, on);
}
