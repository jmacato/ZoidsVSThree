#include "joint.h"

typedef struct CoObjDeep {
    HSD_JObj *joint;
    u8 reserved_04[4];
    f32 field_08;
    u8 reserved_0C[0x8C];
    f32 field_98;
    f32 field_9C;
} CoObjDeep;

void chkDeepCo(CoObjDeep *co, s32 *flag, f32 *depth)
{
    f32 d;
    if (co->joint != 0) {
        d = co->field_98 - (co->field_9C - co->field_08);
        if (d > 0.0f) {
            *flag = 1;
            if (d > *depth)
                *depth = d;
        }
    }
}
