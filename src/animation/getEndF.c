#include "jobj.h"

extern s32 getEndF2(HSD_AObj *animation);

#pragma dont_inline on
s32 getEndF(HSD_JObj *joint)
{
    if (joint == (void *)0)
        return 1;
    if (joint->animation != 0) {
        if (getEndF2(joint->animation) != 0)
            return 1;
        return 0;
    }
    for (joint = joint->child; joint != 0; joint = joint->next) {
        if (getEndF(joint) != 0)
            return 1;
    }
    return 0;
}
