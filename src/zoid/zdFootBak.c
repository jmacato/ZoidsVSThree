#include "zoid3.h"

extern void ik3dAnim(ZoidState *zoid, FootJoint *foot);

void zdFootBak(ZoidState *zoid)
{
    ik3dAnim(zoid, &zoid->feet[2]);
    ik3dAnim(zoid, &zoid->feet[3]);
    ik3dAnim(zoid, &zoid->feet[0]);
    ik3dAnim(zoid, &zoid->feet[1]);
}
