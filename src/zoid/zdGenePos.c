#include "zoid3.h"

extern f32 zdColPosY(f32 *point, u16 *selector);
extern void zdSetXYZ(ZoidState *zoid);
extern void sMakeMatrix(HSD_JObj *joint);
extern void zdFootBak(ZoidState *zoid);
extern void ZoidCopyAnim(ZoidState *zoid);
extern void zdCoStartPos(ZoidState *zoid);

typedef struct ZoidF32Span {
    u8 pad[0x1D14];
    f32 values[3];
} ZoidF32Span;

void zdGenePos(ZoidState *zoid)
{
    s32 i;
    f32 value;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        zoid->position[0] = (f32)zoid->gene_x;
        zoid->position[2] = (f32)zoid->gene_z;
        zoid->position[1] = 100.0f;
        zoid->position[1] = zdColPosY(zoid->position, &zoid->ground_polygon) + 10.0f;
        if (zoid->gene_y_fixed != 0) {
            zoid->position[1] = (f32)zoid->gene_y;
        }
        for (i = 0; i < 3; i++) {
            value = zoid->position[i];
            zoid->field_1A9C[i] = value;
            zoid->field_1C24[i] = value;
            zoid->field_1A80[i] = value;
            zoid->field_1A8C[i] = value;
            zoid->displacement[i] = 0.0f;
            ((ZoidF32Span *)zoid)->values[i] = 0.0f;
            zoid->field_1D20[i] = 0.0f;
            if (zoid->field_1A7C != 0) {
                zoid->field_1A7C->matrix[i][3] = value;
            }
            zoid->child_matrix[i][3] = value;
            zoid->field_1A40[i] = value;
            zoid->clip_point[i] = value;
            zoid->previous_child_translation[i] = value;
            zoid->child_translation[i] = value;
            zoid->previous_position[i] = value;
        }
        zoid->field_1A98 = 0;
        zdSetXYZ(zoid);
        sMakeMatrix(zoid->joint);
        zdFootBak(zoid);
        ZoidCopyAnim(zoid);
        zdCoStartPos(zoid);
    }
}
