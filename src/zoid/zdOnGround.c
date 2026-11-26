#include "zoid3.h"

extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(void *jobj);

void zdOnGround(ZoidState *zoid)
{
    if (zoid->joint != 0) {
        zdSetXYZ(zoid);
        sMakeMatrix(zoid->joint);
    }
}
