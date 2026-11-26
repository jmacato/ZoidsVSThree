#include "joint.h"

typedef struct CoObjMtx {
    HSD_JObj *joint;
    u8 reserved_04[0x34];
    f32 inverse[3][4];
} CoObjMtx;

extern u32 PSMTXInverse(f32 src[3][4], f32 dst[3][4]);

void zdCoObjMtxI(CoObjMtx *object)
{
    if (object != (void *)0 && object->joint != (void *)0)
        PSMTXInverse(object->joint->matrix, object->inverse);
}
