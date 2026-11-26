#include "zoid3.h"
#include "matrix.h"

typedef struct CoObjVS3 {
    HSD_JObj *joint;
    HSD_JObj *base_joint;
    u8 pad_0008[0x30];
    f32 inverse[3][4];
    u8 pad_0068[0x4];
    s32 health;
} CoObjVS3;

extern u32 PSMTXInverse(Mtx source, Mtx destination);
extern void sGlobal2Local(HSD_JObj *joint);

void ZoidCoObjMove(CoObjVS3 *object, f32 *movement, f32 damage)
{
    MtxPtr world;
    MtxPtr base;
    s32 axis;

    if (object != (void *)0 && object->joint != (void *)0 && object->base_joint != (void *)0) {
        world = object->joint->matrix;
        base = object->base_joint->matrix;
        for (axis = 0; axis < 3; axis++) {
            world[axis][3] += movement[axis];
            base[axis][3] += movement[axis];
        }
        PSMTXInverse(world, object->inverse);
        sGlobal2Local(object->base_joint);
        object->health -= (s32)damage;
        if (object->health < 0) {
            object->health = 0;
        }
    }
}
