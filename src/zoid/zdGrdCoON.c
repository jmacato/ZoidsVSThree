#include "zoid3.h"

typedef struct CoObj3 {
    HSD_JObj *joint;
    u8 pad_04[0x14];
    void *ground_contact;
    u8 pad_1C[0x7C];
    f32 ground_y;
} CoObj3;

extern f32 zdColPosY(f32 *point, u16 *selector);

void zdGrdCoON(ZoidState *zoid, CoObj3 *co, s32 flag)
{
    u16 selector;
    f32 position[3];
    f32 depth;
    f32 height;
    s32 axis;

    if (co != (void *)0 && co->joint != (void *)0) {
        for (axis = 0; axis < 3; axis++) {
            position[axis] = co->joint->matrix[axis][3];
        }
        depth = zdColPosY(position, &selector);
        if (zoid->field_0170 != 0 && depth >= position[1] + 1.0f) {
            selector = 0xFFFF;
            depth = position[1] - 0.1;
        }
        if (selector == 0xFFFF) {
            return;
        }
        co->ground_y = depth;
        height = depth - position[1];
        if (height >= 0.0f) {
            zoid->grounded = 1;
            if (zoid->max_ground_depth < height) {
                zoid->max_ground_depth = height;
            }
        }
        if (flag != 0 && co->ground_contact != 0) {
            zoid->grounded = 1;
        }
    }
}
