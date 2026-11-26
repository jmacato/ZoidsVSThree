#include "zoid3.h"

extern void zdOptionUseOnOff1(ZoidState *zoid, s32 on);
extern void zdOptionUseOnOff2(ZoidState *zoid, s32 on);
extern void zdOptionUseOnOff6(ZoidState *zoid, s32 on);

void zdOptionUseOnOff(ZoidState *zoid, s32 on)
{
    if (zoid->option_type == ZOID_OPTION_SHIELD)
        zdOptionUseOnOff1(zoid, on);
    if (zoid->option_type == ZOID_OPTION_BOOSTER)
        zdOptionUseOnOff2(zoid, on);
    if (zoid->option_type == 6)
        zdOptionUseOnOff6(zoid, on);
}
