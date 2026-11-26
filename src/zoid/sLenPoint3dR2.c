#include "types.h"

extern f64 __frsqrte(f64 value);

f32 sLenPoint3dR2(f32 *point)
{
    register f64 estimate;
    f32 sum;
    f32 value;
    f32 result;
    s32 i;
    volatile f32 root;

    sum = 0.0f;
    for (i = 0; i < 3; i++) {
        if (i != 1) {
            value = point[i];
            sum = value * value + sum;
        }
    }
    if (sum > 0.0f) {
        estimate = __frsqrte(sum);

        estimate = 0.5 * estimate * (3.0 - estimate * estimate * sum);
        estimate = 0.5 * estimate * (3.0 - estimate * estimate * sum);
        estimate = 0.5 * estimate * (3.0 - estimate * estimate * sum);
        estimate = 0.5 * estimate * (3.0 - estimate * estimate * sum);
        root = sum * estimate;
        result = root;
    } else {
        result = sum;
    }
    return result;
}
