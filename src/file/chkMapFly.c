#include "types.h"

extern s8 *mgP;
extern u8 IveSave[];
extern void *prmTblGet(s32 index);

s32 chkMapFly(s32 index)
{
    s32 slot;
    void *part;
    if (mgP == 0)
        return 0;
    if (mgP[0x321D] == 0)
        return 0;
    if (index < 0)
        return 0;
    slot = *(s16 *)(IveSave + index * 0x1CB0 + 0x15F4);
    if (slot < 0)
        return 0;
    if (slot >= 0x12C)
        return 0;
    part = prmTblGet(slot);
    if (part == 0)
        return 0;
    if (*(s32 *)((u8 *)part + 0xF8) == 3)
        return 1;
    return 0;
}
