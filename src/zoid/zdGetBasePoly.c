#include "zoid3.h"
#include "ground_collision.h"

extern f32 zdPosY(ZoidState *zoid, u16 *selector);
extern void zdGetDeadPoly(ZoidState *zoid, f32 *point);

f32 zdGetBasePoly(ZoidState *zoid, f32 *point)
{
    GroundMask *mask = 0;
    Vec3 *normal = 0;
    u16 selector;
    u16 original;
    GroundMask *cell;
    u32 material;
    f32 y;
    f32 result;

    y = zdPosY(zoid, &selector);
    original = selector;
    if (y >= zoid->field_1AA8) {
        y = zoid->position[1];
        selector = GROUND_POLYGON_NONE;
    }
    if (selector != GROUND_POLYGON_NONE) {
        material = grdcPolygon[selector].material;
        cell = &grdcMat[material];
        mask = cell;
        if (zoid->ai_active == 0) {
            if (mask->bits[0] & 4) {
                zoid->field_1E74 = 1;
                if (zoid->death_started == 0)
                    zoid->death_started = 1;
            }
        } else {
            if (mask->bits[0] & 6)
                zoid->field_1E78++;
            else
                zoid->field_1E78 = 0;
        }
        if (mask->bits[2] & 2)
            zoid->field_1E7C = 1;
        normal = &grdcNormal[grdcPolygon[selector].normal_index];
    }
    zoid->ground_material = mask;
    zoid->ground_polygon = selector;
    zoid->field_1EB8 = original;
    zoid->ground_normal = normal;
    result = y;
    zdGetDeadPoly(zoid, point);
    return result;
}
