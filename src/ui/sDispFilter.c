#include "zoid3.h"
#include "game_camera.h"

extern void sDispGameFilter(s32 index, s32 mode);

void sDispFilter(CameraState *camera, ZoidState *zoid)
{
    s32 index;
    s32 hit;
    s32 mode;

    if (zoid == (void *)0)
        return;
    index = camera->half;
    if (sCamNN == 1)
        index = 0;
    hit = 0;
    mode = 0;
    if (zoid->ally_smoke_timer != 0 || zoid->enemy_smoke_timer != 0)
        hit = 1;
    if (hit != 0)
        mode = 1;
    sDispGameFilter(index, mode);
}
