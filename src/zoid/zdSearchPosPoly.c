#include "zoid3.h"
#include "ground_collision.h"

extern f32 zdColPosY(f32 *point, u16 *selector);

void zdSearchPosPoly(ZoidState *zoid)
{
    u16 selector;
    GroundPolygon *polygon;
    s32 vertex;
    s32 i;

    if (zoid != 0 && zoid->joint != 0) {
        zdColPosY(zoid->position, &selector);
        if (selector == GROUND_POLYGON_NONE) {
            polygon = grdcPolygon;
            if (polygon != 0) {
                vertex = polygon->vertices[0];
                for (i = 0; i < 3; i++) {
                    zoid->position[i] = ((f32 *)&grdcVtx[vertex])[i];
                }
            } else {
                for (i = 0; i < 3; i++) {
                    zoid->position[i] = 0.0f;
                }
            }
        }
    }
}
