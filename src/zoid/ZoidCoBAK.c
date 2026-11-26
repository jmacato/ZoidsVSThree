#include "zoid3.h"

typedef struct CoObjV3 {
    HSD_JObj *joint;
    HSD_JObj *base_joint;
    u8 reserved_08[0x6C];
    f32 position[3];
    f32 base_position[3];
    f32 movement[3];
    u8 reserved_98[4];
    f32 field_9C;
} CoObjV3;

void ZoidCoBAK(ZoidState *zoid, CoObjV3 *object)
{
    s32 axis;

    if (zoid == (void *)0) {
        return;
    }
    if (zoid->joint == 0) {
        return;
    }
    if (object == (void *)0) {
        return;
    }
    if (object->joint == (void *)0) {
        return;
    }
    for (axis = 0; axis < 3; axis++) {
        object->movement[axis] = object->joint->matrix[axis][3] - object->position[axis];
        object->position[axis] = object->joint->matrix[axis][3];
        if (object->base_joint != 0) {
            object->base_position[axis] = object->base_joint->matrix[axis][3];
        }
    }
    object->field_9C = object->joint->matrix[1][3];
}
