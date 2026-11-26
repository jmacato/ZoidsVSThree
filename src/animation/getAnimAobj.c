#include "joint.h"
#include "dobj.h"
#pragma dont_inline on

struct HSD_AObj *getAnimAobj(HSD_JObj *joint)
{
    struct HSD_AObj *animation;
    HSD_JObj *parent;
    HSD_DObj *dobj;
    if (joint == (void *)0) {
        return 0;
    }
    if (joint->animation != 0) {
        return joint->animation;
    }
    parent = joint;
    for (joint = joint->child; joint != 0; joint = joint->next) {
        animation = getAnimAobj(joint);
        if (animation != 0) {
            return animation;
        }
    }
    dobj = parent->display_object;
    if (dobj != 0 && dobj->aobj != 0) {
        return dobj->aobj;
    }
    return 0;
}
