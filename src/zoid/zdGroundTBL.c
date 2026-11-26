#include "zoid3.h"
#include "ground_collision.h"

extern s32 zdCgTblChk2(ZoidState *zoid, u16 index);
extern s32 zdGroundPoly(ZoidState *zoid, u16 index, GroundPolygon *polygon, s32 a, s32 b, s32 c);

s32 zdGroundTBL(ZoidState *zoid, u16 *table, s32 a, s32 b, s32 c)
{
    s32 hit;
    u16 index;
    GroundPolygon *polygon;
    s32 material;
    GroundMask *mask;

    hit = 0;
    while (1) {
        index = *table;
        table++;
        if (index == GROUND_POLYGON_NONE) {
            return hit;
        }
        if (zdCgTblChk2(zoid, index)) {
            zoid->field_40FC++;
        } else {
            polygon = &grdcPolygon[index];
            material = polygon->material;
            mask = &grdcMat[material];
            if ((mask->bits[0] & 0x17) != 0) {
                if (zdGroundPoly(zoid, index, polygon, a, b, c)) {
                    hit = 1;
                }
            }
        }
    }
}
