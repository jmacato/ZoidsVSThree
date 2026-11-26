#include "zoid3.h"
#include "ground_collision.h"

void zdGetDeadPoly(ZoidState *zoid, Vec3 *point)
{
    u16 selector;
    GroundMask filter = (GroundMask){{8, 0, 0, 0}};
    f32 y;
    GroundMask *mask;
    s32 material;
    GroundMask *mask2;

    y = sColPosAndY((Vec3 *)zoid->position, &selector, &filter);
    if (selector != GROUND_POLYGON_NONE) {
        material = grdcPolygon[selector].material;
        mask = &grdcMat[material];
        mask2 = mask;
        if (point->y <= y) {
            if ((mask2->bits[0] & 0x08) != 0) {
                zoid->health = 0;
                zoid->knockback[1] = 3.0f;
                zoid->knockback[0] = 0.0f;
                zoid->knockback[2] = 0.0f;
            }
        }
    }
}
