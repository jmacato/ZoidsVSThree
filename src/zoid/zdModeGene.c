#include "zoid3.h"

extern void zdGenePos(ZoidState *zoid);
extern f32 zdColPosY(Vec3 *point, u16 *selector);

void zdModeGene(ZoidState *zoid)
{
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        zoid->gene_frames++;
        zdGenePos(zoid);
        if (zoid->gene_frames > 15) {
            zoid->action = 0;
            zoid->requested_action = 2;
            zoid->death_pending = 0;
            zoid->position[1] = 100.0f;
            if (zoid->gene_y_fixed != 0) {
                zoid->position[1] = (f32)zoid->gene_y;
            } else {
                zoid->position[1] = 1.0f + zdColPosY((Vec3 *)zoid->position, (u16 *)0);
            }
            zoid->position[0] = (f32)zoid->gene_x;
            zoid->position[2] = (f32)zoid->gene_z;
        }
    }
}
