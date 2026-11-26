#include "zoid3.h"
#include "zoid_ai.h"
#include "ground_collision.h"

extern void aiCmdReport(const char *msg);

inline f32 absf(f32 value)
{
    *(u32 *)&value &= 0x7FFFFFFF;
    return value;
}

s32 zdAI_WarningArea(s32 index)
{
    s32 polygon_index;
    s32 material;
    GroundMask *material_mask;
    GroundMask *mask;
    f32 offset;

    aiCmdReport("aiCmd-WarnninArea \n");
    if (index < 0) {
        return 0;
    }
    if (index >= 16) {
        return 0;
    }
    {
        ZoidState *zoid = &Zoid[index];
        if (zoid->joint == (void *)0) {
            return 0;
        }
        offset = absf(zoid->joint->matrix[0][3]);
        if (offset > 2900.0f) {
            return 1;
        }
        offset = absf(zoid->joint->matrix[2][3]);
        if (offset > 2900.0f) {
            return 1;
        }
        polygon_index = zoid->ground_polygon;
        if (polygon_index == GROUND_POLYGON_NONE) {
            return 1;
        }
        material = grdcPolygon[polygon_index].material;
        material_mask = &grdcMat[material];
        mask = material_mask;
        if (zoid->field_1E78 > 60) {
            return 1;
        }
        if (mask->bits[0] & 4) {
            return 1;
        }
        return 0;
    }
}
