#include "zoid3.h"

extern void zdSmokeForce(FootJoint *foot);

void ssSmoke(ZoidState *zoid)
{
    zdSmokeForce(&zoid->feet[0]);
    zdSmokeForce(&zoid->feet[1]);
    zdSmokeForce(&zoid->feet[2]);
    zdSmokeForce(&zoid->feet[3]);
}
