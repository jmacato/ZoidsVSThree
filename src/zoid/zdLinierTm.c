#include "zoid3.h"

void zdLinierTm(ZoidState *zoid, s32 duration)
{
    zoid->interpolation_remaining = duration;
    zoid->interpolation_duration = duration;
}
