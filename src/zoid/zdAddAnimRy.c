#include "zoid3.h"

extern void zdColPosY(f32 *position, u16 *polygon);

void zdAddAnimRy(ZoidState *zoid)
{
    HSD_JObj *joint;
    s32 i;
    u16 polygon;

    if (zoid != (void *)0) {
        joint = zoid->joint;
        if (joint != (void *)0 && (joint = joint->child) != (void *)0) {
            for (i = 0; i < 3; i++) {
                zoid->position[i] = zoid->child_matrix[i][3];
            }
            zdColPosY(zoid->position, &polygon);
            if (polygon == 0xFFFF) {
                for (i = 0; i < 3; i++) {
                    zoid->position[i] = zoid->previous_position[i];
                }
            }
            zoid->heading += zoid->heading_delta;
            zoid->height_offset = 0.0f;
        }
    }
}
