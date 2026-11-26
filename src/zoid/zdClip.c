#include "zoid3.h"

extern s32 sCamNN;
extern void PSMTXMultVec(f32 matrix[3][4], Vec3 *source, Vec3 *destination);

s32 zdClip(s32 flag, f32 matrix[3][4], ZoidState *zoid, Vec3 *out)
{
    f32 scale;
    f32 limit;
    f32 height;
    s32 i;

    height = *(f32 *)((u8 *)zoid->body_coobj + 0x10);
    scale = 0.0f;
    limit = 20.0f;
    if (height > 30.0f) {
        scale = 1.0f;
        limit += height;
    }
    for (i = 0; i < 3; i++) {
        zoid->clip_point[i] = ((HSD_JObj *)zoid->camera_joint)->matrix[i][3];
    }
    PSMTXMultVec(matrix, (Vec3 *)zoid->clip_point, out);
    if (out->z >= height * scale + 20.0f) {
        return 1;
    }
    if (flag == 0 && out->z < -600.0f) {
        return 1;
    }
    if (sCamNN == 1) {
        if (out->x + out->z >= limit) {
            return 1;
        }
        if (out->x - out->z <= -limit) {
            return 1;
        }
    }
    return 0;
}
