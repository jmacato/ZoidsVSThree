#include "zoid3.h"

extern void ZoidInertia(ZoidState *zoid);

void ZoidInertiaAtk(ZoidState *zoid)
{
    s32 axis;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        if (zoid->field_1EB0 != 0 || zoid->field_1EB2 != 0 || zoid->field_1EAE != 0xFFFF) {
            zoid->ground_turn = 0xF;
            for (axis = 0; axis < 3; axis++)
                zoid->displacement[axis] = 0.0f;
        }
        if (zoid->ground_turn != 0) {
            zoid->displacement[0] = 0.0f;
            zoid->displacement[2] = 0.0f;
            if (zoid->displacement[1] > 0.0f)
                zoid->displacement[0] = 0.0f;
        }
        ZoidInertia(zoid);
    }
}
