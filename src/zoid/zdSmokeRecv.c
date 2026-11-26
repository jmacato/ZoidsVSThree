#include "zoid3.h"

void zdSmokeRecv(ZoidState *zoid)
{
    if (zoid != 0 && zoid->joint != 0) {
        if (zoid->ally_smoke_timer != 0) {
            zoid->ally_smoke_timer--;
        }
        if (zoid->enemy_smoke_timer != 0) {
            zoid->enemy_smoke_timer--;
            zoid->target_pending = 0;
            if (zoid->ai != 0) {
                zoid->ai->target_index = -1;
            }
        }
    }
}
