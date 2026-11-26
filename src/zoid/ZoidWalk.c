#include "zoid3.h"

extern void ZoidWalkSumuSpd(ZoidState *zoid);
extern void ZoidWalkSusumu(ZoidState *zoid);
extern void ZoidWalkSusumu3(ZoidState *zoid);

void ZoidWalk(ZoidState *zoid)
{
    s32 i = 0;
    if (zoid) i = 0;
    ZoidWalkSumuSpd(zoid);
    if (zoid->field_0170 != 0) {
        ZoidWalkSusumu3(zoid);
    } else {
        ZoidWalkSusumu(zoid);
    }
}
