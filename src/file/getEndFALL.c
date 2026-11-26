#include "jobj.h"
#include "dobj.h"
#include "mobj.h"

extern s32 getEndF2(struct HSD_AObj *aobj);
extern s32 getEndFALL(HSD_JObj *joint);

s32 getEndFALL(HSD_JObj *joint)
{
    HSD_JObj *root;
    HSD_DObj *dobj;
    HSD_MObj *mobj;

    if (joint == (void *)0)
        return 1;
    if (joint->animation != 0) {
        if (getEndF2(joint->animation) != 0)
            return 1;
        return 0;
    }
    root = joint;
    joint = joint->child;
    while (joint != 0) {
        if (getEndFALL(joint) != 0)
            return 1;
        joint = joint->next;
    }
    dobj = root->display_object;
    if (dobj == 0)
        return 0;
    if (dobj->aobj != 0 && getEndF2(dobj->aobj) != 0)
        return 1;
    mobj = dobj->mobj;
    if (mobj == 0)
        return 0;
    if (mobj->aobj != 0 && getEndF2(mobj->aobj) != 0)
        return 1;
    return 0;
}
