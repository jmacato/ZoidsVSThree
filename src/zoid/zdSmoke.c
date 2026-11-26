#include "zoid3.h"

extern void ftSmoke(ZoidState *zoid, FootJoint *foot, s32 frame);

void zdSmoke(ZoidState *zoid)
{
    s32 frame;
    s32 flag;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        frame = zoid->current_animation;
        flag = 1;
        if (frame == 1)
            frame = 2;
        ftSmoke(zoid, &zoid->feet[0], 0);
        ftSmoke(zoid, &zoid->feet[1], 0);
        ftSmoke(zoid, &zoid->feet[2], frame);
        ftSmoke(zoid, &zoid->feet[3], frame);
    }
}
