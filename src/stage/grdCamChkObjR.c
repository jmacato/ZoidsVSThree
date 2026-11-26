#include "types.h"
#include "joint.h"

typedef struct CameraState3 {
    u8 pad_000[0x214];
    Vec3 relative_origin;
    u8 pad_220[0x254 - 0x220];
    f32 planar[2];
    u8 pad_25C[0x2FB - 0x25C];
    s8 clip_disabled;
} CameraState3;

extern CameraState3 *camTmp;
extern s32 sDispClipOnOff;

static inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

s32 grdCamChkObjR(HSD_JObj *joint)
{
    f32 dx;
    f32 dz;
    f32 side;
    f32 forward;

    if (joint == 0)
        return 0;
    dx = joint->matrix[0][3] - camTmp->relative_origin.x;
    dz = joint->matrix[2][3] - camTmp->relative_origin.z;
    if (camTmp->clip_disabled != 0)
        return 1;
    if (sDispClipOnOff == 2) {
        if (absf(dx) > 800.0f)
            return 0;
        if (absf(dz) > 800.0f)
            return 0;
    }
    if (dx * dx + dz * dz > 640000.0f)
        return 0;
    side = dx * camTmp->planar[0] - dz * camTmp->planar[1];
    forward = dx * camTmp->planar[1] + dz * camTmp->planar[0];
    if (forward < -800.0f)
        return 0;
    if (forward > 1100.0f)
        return 0;
    if (side > 1000.0f)
        return 0;
    if (side < -1000.0f)
        return 0;
    if (side - forward > 800.0f)
        return 0;
    if (side + forward < -800.0f)
        return 0;
    return 1;
}
