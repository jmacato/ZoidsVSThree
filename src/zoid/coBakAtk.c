#include "zoid3.h"

extern void ZoidInertiaAtk(ZoidState *zoid);

void coBakAtk(ZoidState *zoid)
{
    s32 axis;

    for (axis = 0; axis < 3; axis++)
        zoid->displacement[axis] = *(f32 *)((u8 *)zoid + 0x4F8 + axis * 4);
    ZoidInertiaAtk(zoid);
}
