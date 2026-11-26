#include "joint.h"

typedef struct CoObj3 {
    HSD_JObj *joint;
    u8 reserved_04[0x20];
    u32 flags;
} CoObj3;

extern void sEffectSet(s32 type, s32 mode, f32 *position, HSD_JObj *source, struct ZoidState *zoid);

void zdSmokeForce(CoObj3 *co)
{
    HSD_JObj *joint;
    u32 flags;

    if (co != (void *)0) {
        joint = co->joint;
        if (joint != 0) {
            flags = co->flags;
            if (flags & 1) {
                sEffectSet(0x39, 1, 0, joint, 0);
            }
        }
    }
}
