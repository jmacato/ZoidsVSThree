#include "ground_collision.h"

static inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

f32 sColPosLessAndY(Vec3 *point, u16 *selector, GroundMask *mask, f32 limit)
{
    u16 *table;
    u16 index;
    u16 best_index;
    u16 material_index;
    s32 normal_index;
    GroundMask *material;
    f32 y;
    f32 best_y;
    f32 distance;
    f32 best_distance;

    if (selector != (void *)0)
        *selector = GROUND_POLYGON_NONE;
    table = sColPosTBL(point);
    if (table == (void *)0)
        return point->y;
    best_y = point->y;
    best_index = GROUND_POLYGON_NONE;
    while (1) {
        index = *table;
        if (index == GROUND_POLYGON_NONE)
            break;
        if (sColPosPolygonON(point, index) == 0)
            goto next;
        normal_index = grdcPolygon[index].normal_index;
        if (grdcNormal[normal_index].y < 0.0f)
            goto next;
        material_index = grdcPolygon[index].material;
        material = &grdcMat[material_index];
        if (!(material->bits[0] & mask->bits[0]) && !(material->bits[1] & mask->bits[1]) &&
            !(material->bits[2] & mask->bits[2]))
            goto next;
        y = sColGetPolyY(index, point);
        if (y > limit)
            goto next;
        distance = absf(y - point->y);
        if (best_distance > distance || best_index == GROUND_POLYGON_NONE) {
            best_y = y;
            best_index = index;
            best_distance = distance;
        }
    next:
        table++;
    }
    if (selector != (void *)0)
        *selector = best_index;
    return best_y;
}
