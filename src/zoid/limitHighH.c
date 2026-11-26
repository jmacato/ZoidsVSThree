#include "types.h"

extern u8 mgI[];

f32 limitHighH(void)
{
    return (f32)*(s32 *)(mgI + 0x3248);
}
