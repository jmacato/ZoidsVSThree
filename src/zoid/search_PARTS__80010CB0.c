#include "model_archive.h"
#include "archive.h"

#pragma dont_inline on

static HSD_JObj *search_PARTS(HSD_JObj *joint, HSD_JObjDesc *description,
                              HSD_JObjDesc *target)
{
    HSD_JObj *match;

    while (joint != 0 && description != 0) {
        if (description == target) {
            return joint;
        }
        if (description->child != 0) {
            match = search_PARTS(joint->child, description->child, target);
            if (match != 0) {
                return match;
            }
        }
        joint = joint->next;
        description = description->next;
    }
    return 0;
}
