#include "zoid3.h"

extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void zdLinearAnimAllBak(ZoidState *zoid);

void zdChgAction(ZoidState *zoid)
{
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        void *anim = zoid->anim_data;
        s32 field = (s32)zoid->slider_info;

        zdSetXYZ(zoid);
        sMakeMatrix(zoid->joint);
        zdLinearAnimAllBak(zoid);
    }
}
