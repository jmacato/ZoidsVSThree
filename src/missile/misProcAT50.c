#include "types.h"
#include "matrix.h"
#include "joint_matrix.h"
#include "angle.h"

typedef struct Missile3 {
    u8 pad_00[0x58];
    f32 matrix[3][4];
    u8 pad_88[0xBC - 0x88];
    f32 inverse[3][4];
    s32 update_count;
    u8 pad_F0[0x10C - 0xF0];
    s32 proc_delay;
} Missile3;

extern void PSMTXRotRad(Mtx m, char axis, f32 rad);

void misProcAT50(Missile3 *missile, Vec3 *target)
{
    Vec3 local;
    Mtx rot;
    f32 angle;

    PSMTXMultVec(missile->inverse, target, &local);
    if ((missile->update_count & 0x20) && local.x < 0.0f) {
        PSMTXRotRad(rot, 'Z', DEG2RAD_F(1.0f));
        PSMTXConcat(missile->matrix, rot, missile->matrix);
    } else {
        angle = 0.0f;
        if (local.z > 0.0f) {
            angle = -DEG2RAD_F(1.0f);
        }
        if (local.z < 0.0f) {
            angle = DEG2RAD_F(1.0f);
        }
        if (angle != 0.0f) {
            PSMTXRotRad(rot, 'Y', angle);
            PSMTXConcat(missile->matrix, rot, missile->matrix);
        }
        angle = 0.0f;
        if (local.y > 0.0f) {
            angle = DEG2RAD_F(1.0f);
        }
        if (local.y < 0.0f) {
            angle = -DEG2RAD_F(1.0f);
        }
        if (angle != 0.0f) {
            PSMTXRotRad(rot, 'Z', angle);
            PSMTXConcat(missile->matrix, rot, missile->matrix);
        }
    }
}
