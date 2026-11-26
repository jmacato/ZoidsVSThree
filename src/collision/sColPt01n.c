#include "ground_collision.h"

extern f32 sColPt00(Vec3 *start, Vec3 *end, GroundPolygon *polygon, GroundMask *mask);

f32 sColPt01n(Vec3 *start, Vec3 *end, u16 *indices, GroundMask *mask, u16 *selector)
{
    GroundMask mask_copy;
    GroundPolygon *polygon;
    f32 fraction;

    if (selector)
        *selector = GROUND_POLYGON_NONE;
    if (indices == (void *)0)
        return GROUND_NO_HIT;
    while (*indices != GROUND_POLYGON_NONE) {
        polygon = &grdcPolygon[*indices];
        mask_copy = *mask;
        fraction = sColPt00(start, end, polygon, &mask_copy);
        if (fraction != GROUND_NO_HIT) {
            if (selector)
                *selector = *indices;
            return fraction;
        }
        indices++;
    }
    return GROUND_NO_HIT;
}
