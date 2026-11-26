#include "zoid3.h"

extern void zdGetBasePoly(ZoidState *zoid, f32 *position);

void ZoidInertia(ZoidState *zoid)
{
    s32 axis;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        zoid->displacement[1] -= 0.025;
        if (zoid->grounded != 0 || zoid->field_1EB0 != 0 || zoid->field_1EB2 != 0 || zoid->field_1EAE != 0xFFFF) {
            for (axis = 0; axis < 3; axis++) {
                if (axis == 1) {
                    zoid->displacement[1] -= 0.005000000000000001;
                }
                zoid->displacement[axis] *= 0.59;
            }
        }
        if (zoid->field_1EB0 != 0 || zoid->field_1EB2 != 0) {
            for (axis = 0; axis < 3; axis++) {
                zoid->displacement[axis] = 0.0f;
            }
        }
        for (axis = 0; axis < 3; axis++) {
            zoid->position[axis] += zoid->displacement[axis];
        }
        zdGetBasePoly(zoid, zoid->position);
    }
}
