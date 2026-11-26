#include "zoid3.h"

void zdAtack1(ZoidState *zoid)
{
    if (zoid == (void *)0) return;
    if (zoid->joint == (void *)0) return;
    zoid->requested_action = 13;
    if (zoid->field_0170 == 0) return;
    zoid->requested_action = 52;
}
