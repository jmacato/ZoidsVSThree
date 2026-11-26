#include "aobj.h"

extern u32 HSD_AObjGetFlags(HSD_AObj *animation);

s32 getEndF2(HSD_AObj *animation)
{
    u32 flags;
    if (animation == 0)
        return 0;
    flags = HSD_AObjGetFlags(animation);
    if (flags & AOBJ_REWINDED)
        return 1;
    if (flags & AOBJ_NO_ANIM)
        return 1;
    if (animation->flags & AOBJ_REWINDED)
        return 1;
    animation = 0;
    return 0;
}
