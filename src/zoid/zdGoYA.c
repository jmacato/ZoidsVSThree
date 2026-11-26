#include "zoid3.h"
#include "ground_collision.h"

extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);
extern f32 atan2f(f32 y, f32 x);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void PSMTXRotRad(f32 m[3][4], char axis, f32 rad);
extern void PSMTXMultVecSR(f32 m[3][4], Vec3 *src, Vec3 *dst);

f32 zdGoYA(ZoidState *zoid, f32 angle, f32 distance)
{
    register f32 result;
    f32 ny;
    f32 origin[3];
    f32 target[3];
    u16 selector;
    f32 mtx[3][4];
    void *control;
    Vec3 normal;
    s32 axis;
    f32 pb;
    f32 sin_angle;
    f32 cos_angle;
    f32 dy;

    if (zoid == (void *)0)
        return 0.0f;
    if (zoid->joint == (void *)0)
        return 0.0f;
    control = zoid->anim_data;
    if (0.0f == distance) {
        Vec3 *ground;
        if (zoid->ground_polygon == GROUND_POLYGON_NONE)
            return 0.0f;
        ground = &grdcNormal[grdcPolygon[zoid->ground_polygon].normal_index];
        PSMTXRotRad(mtx, 'Y', -zoid->heading - angle);
        PSMTXMultVecSR(mtx, ground, &normal);
        ny = normal.y;
        result = -atan2f(normal.z, ny);
        return result;
    }
    for (axis = 0; axis < 3; axis++) {
        origin[axis] = zoid->position[axis];
        target[axis] = zoid->position[axis];
    }
    if (zoid->field_0170 == 0) {
        origin[1] = zoid->ground_height;
        target[1] = zoid->ground_height;
    }
    sin_angle = angle + zoid->heading;
    target[0] += distance * sinf(sin_angle);
    cos_angle = angle + zoid->heading;
    target[2] += distance * cosf(cos_angle);
    target[1] = zdColPosY(target, &selector);
    dy = target[1] - origin[1];
    pb = atan2f(dy, distance);
    return pb;
}
