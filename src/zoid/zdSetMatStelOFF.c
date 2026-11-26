#include "zoid3.h"

extern void ZoidCopyMatRet(ZoidState *zoid);

void zdSetMatStelOFF(ZoidState *zoid)
{
    if (zoid != (ZoidState *)0 && zoid->joint != (HSD_JObj *)0) {
        ZoidCopyMatRet(zoid);
    }
}
