#include "types.h"

extern void MemCpy(void *dst, const void *src, u32 size);

extern u8 fixt[];
extern s32 *fixSt;
extern s32 *fix;

void fixSave(void)
{
    MemCpy(fixSt, fixt, 0x7318);
    fix = fixSt;
    *fix = -1;
}
