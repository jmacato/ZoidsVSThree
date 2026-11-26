#include "types.h"

s32 chkPos(f32 *a, f32 *b)
{
    s32 i;
    f32 diff;
    for (i = 0; i < 3; i++) {
        diff = a[i] - b[i];
        if (i == 1)
            diff = diff / 10.0f;
        if ((s32)diff != 0)
            return 0;
    }
    return 1;
}
