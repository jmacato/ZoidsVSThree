#include "zoid3.h"

void chkDeep(FootJoint *foot, s32 *found, f32 *minimum)
{
    if (!(foot->depth > 0.0f)) return;
    *found = 1;
    if (foot->depth < *minimum) {
        *minimum = foot->depth;
    }
}
