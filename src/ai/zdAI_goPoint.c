#include "zoid3.h"
#include "zoid_ai.h"

extern void aiCmdReport(const char *msg);
extern void goFrom(ZoidState *zoid);
extern f32 zdColPosY(Vec3 *point, s32 selector);

void zdAI_goPoint(s32 index, f32 x, f32 z)
{
    ZoidState *zoid;
    ZoidAIState *ai;

    aiCmdReport("aiCmd-goPoint \n");
    if (index >= 0 && index < 16) {
        zoid = &Zoid[index];
        if (zoid->joint != (void *)0) {
            ai = zoid->ai;
            if (ai != (void *)0) {
                goFrom(zoid);
                ai->mode = AI_MODE_POINT;
                ai->flags = AI_RADIUS_IN;
                ai->target_distance = 5.0f;
                ai->destination.x = x;
                ai->destination.z = z;
                ai->destination.y = 100.0f;
                ai->destination.y = zdColPosY(&ai->destination, 0);
            }
        }
    }
}
