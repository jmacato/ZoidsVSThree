#include "ground_collision.h"
#include "matrix.h"

typedef struct CoObj3 {
    u8 reserved_00[0x38];
    f32 inverse[3][4];
} CoObj3;

extern s32 sCubeInPoly(s32 count, Vec3 *vertices);

s32 zdGrdCoPo00(CoObj3 *object, GroundPolygon *polygon)
{
    Vec3 local[6];
    s32 count;
    s32 i;
    s32 index;

    if (object == 0)
        return 0;
    count = polygon->vertex_count;
    for (i = 0; i < count; i++) {
        index = polygon->vertices[i];
        PSMTXMultVec(object->inverse, &grdcVtx[index], &local[i]);
    }
    return sCubeInPoly(count, local);
}
