#include "jobj.h"
#pragma dont_inline on

HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth,
                   s32 fifth)
{
    s32 dead;
    s32 indices[6];
    register s32 *index;

    if (first == -1)
        return joint;
    if (joint == 0)
        return 0;
    indices[0] = first;
    indices[1] = second;
    indices[2] = third;
    indices[3] = fourth;
    indices[4] = fifth;
    indices[5] = -1;
    index = indices;
    do {
        for (first = *index; first > 0; first--) {
            joint = joint != 0 ? joint->next : 0;
            if (joint == (void *)0)
                return 0;
        }
        if (*++index == -1)
            return joint;
        joint = joint != 0 ? joint->child : 0;
    } while (joint != 0);
    return 0;
}
