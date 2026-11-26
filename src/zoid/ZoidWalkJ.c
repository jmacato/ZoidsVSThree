#include "zoid3.h"
#include "ground_collision.h"

extern f32 zdColPosY(Vec3 *point, u16 *selector);
extern void ZoidSisei(ZoidState *zoid);
extern void getWarn(Vec3 *from, Vec3 *to);
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);

void ZoidWalkJ(ZoidState *zoid)
{
    f32 dx;
    f32 dz;
    Vec3 position;
    f32 height;
    u16 selector;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        dx = zoid->displacement[0];
        dz = zoid->displacement[2];
        position.x = zoid->position[0] + dx;
        position.y = zoid->position[1];
        position.z = zoid->position[2] + dz;
        height = zdColPosY(&position, &selector);
        zoid->ground_polygon = selector;
        if (selector == GROUND_POLYGON_NONE) {
            getWarn((Vec3 *)zoid->position, &position);
            zoid->heading += ZoidCalcAngle(zoid, &position);
        } else {
            zoid->position[0] += dx;
            zoid->position[2] += dz;
            ZoidSisei(zoid);
        }
    }
}
