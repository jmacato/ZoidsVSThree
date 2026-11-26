#include "zoid3.h"

void ftSlide(ZoidState *zoid)
{
    s32 dead;
    register s32 i;
    f32 limit;
    f32 slide[3];
    f32 offset;

    dead = 0;
    limit = 0.3f;
    if (zoid->ground_normal_count != 0) {
        for (i = 0; i < 3; i++) {
            offset = zoid->ground_normal_sum[i] / (f32)zoid->ground_normal_count;
            if (offset > 0.0f) {
                offset -= limit;
                if (offset < 0.0f) {
                    offset = 0.0f;
                }
            }
            if (offset < 0.0f) {
                offset += limit;
                if (offset > 0.0f) {
                    offset = 0.0f;
                }
            }
            if (offset) {
                (void)0;
            }
            slide[i] = 0.1 * offset;
            dead = 0;
        }
        zoid->position[0] += slide[0];
        zoid->position[2] += slide[2];
    }
}
