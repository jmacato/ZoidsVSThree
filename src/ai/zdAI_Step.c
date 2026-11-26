#include "zoid3.h"
#include "zoid_ai.h"
#include "ground_collision.h"

extern void aiCmdReport(const char *msg);
extern void zdStep1(ZoidState *zoid, s32 degrees);
extern void getWarn(Vec3 *position, Vec3 *warn);
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *warn);
extern void angLimit(f32 *angle);

void zdAI_Step(s32 index, s32 degrees)
{
    ZoidState *zoid;
    GroundMask *mask;
    Vec3 warn;
    f32 angle;
    s32 step;

    aiCmdReport("aiCmd-step \n");
    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0) {
            mask = zoid->ground_material;
            step = degrees;
            degrees = 0;
            if (mask != 0 && (mask->bits[0] & 0x10)) {
                getWarn((Vec3 *)zoid->position, &warn);
                angle = ZoidCalcAngle(zoid, &warn);
                angLimit(&angle);
                step = (s32)(360.0 * (angle / (2.0 * 3.1415926)));
            }
            zdStep1(zoid, step);
        }
    }
    degrees = 0;
}
