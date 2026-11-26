#include "zoid3.h"
#include "ground_collision.h"

extern double cos(double);
extern f32 sAngPoint3dR(f32 *a, Vec3 *b);

s32 zdClimb(ZoidState *zoid, Vec3 *point)
{
    f32 diff[3];
    s32 i;
    u16 selector;
    Vec3 *normal;
    u32 index;
    f32 slope;

    if (zoid->position[1] > point->y) {
        return 0;
    }
    selector = zoid->ground_polygon;
    if (selector == 0xFFFF) {
        return 0;
    }
    index = grdcPolygon[selector].normal_index;
    normal = grdcNormal + index;
    for (i = 0; i < 3; i++) {
        diff[i] = ((f32 *)point)[i] - zoid->position[i];
    }
    if (normal->y >= cos(1.0471975333333332)) {
        return 0;
    }
    slope = sAngPoint3dR(diff, normal);
    if (slope >= 0.0f) {
        return 0;
    }
    if (slope >= -0.2) {
        return 0;
    }
    return 1;
}
