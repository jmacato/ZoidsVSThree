#include "types.h"

extern u8 mgI[];

f32 limitHighL(void)
{
    return (f32)*(s32 *)(mgI + 0x324C);
}
