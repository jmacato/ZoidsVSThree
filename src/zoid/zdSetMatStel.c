#include "zoid3.h"

extern void *steMobj;
extern void ZoidCopyMatSet(ZoidState *zoid, void *material);

void zdSetMatStel(ZoidState *zoid)
{
    if (zoid != (ZoidState *)0 && zoid->joint != (HSD_JObj *)0) {
        ZoidCopyMatSet(zoid, steMobj);
    }
}
