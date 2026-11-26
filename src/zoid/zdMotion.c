#include "zoid3.h"

void zdMotion(ZoidState *zoid, s32 motion)
{
    if (zoid == 0)
        return;
    if (zoid->joint == 0)
        return;
    if (zoid->death_started != 0)
        return;
    if (zoid->action != 0)
        return;
    if (zoid->requested_action != 0)
        return;
    zoid->field_1DEC = motion;
    zoid->requested_action = 0x31;
}
