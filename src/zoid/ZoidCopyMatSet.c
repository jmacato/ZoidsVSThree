#include "zoid3.h"
#include "dobj.h"

extern void stCopyMatSet(HSD_JObj *joint, HSD_MObj *material);

void ZoidCopyMatSet(ZoidState *zoid, HSD_MObj *material)
{
    stCopyMatSet(zoid->joint, material);
}
