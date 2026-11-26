#include "joint.h"

#pragma dont_inline on

extern void HSD_AObjSetRate(struct HSD_AObj *animation, f32 value);

void setAnimRate(HSD_JObj *joint, f32 value)
{
    if (joint != (void *)0) {
        if (joint->animation != 0) {
            HSD_AObjSetRate(joint->animation, value);
        }
        for (joint = joint->child; joint != 0; joint = joint->next) {
            setAnimRate(joint, value);
        }
    }
}
