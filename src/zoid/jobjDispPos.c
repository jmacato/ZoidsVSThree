#include "jobj.h"

extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);

#pragma dont_inline on
void jobjDispPos(HSD_JObj *joint, HSD_JObj *source)
{
    if (joint != (void *)0) {
        jobjCopyPos(source, joint);
        HSD_JObjDisp(joint, 0, HSD_TRSP_ALL, 0);
    }
}
