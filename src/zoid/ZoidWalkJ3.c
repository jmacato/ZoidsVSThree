#include "zoid3.h"

extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);
extern f32 sLenXZ(f32 x, f32 z);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void getWarn(f32 *position, f32 *point);
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);
extern void ZoidSisei(ZoidState *zoid);

void ZoidWalkJ3(ZoidState *zoid)
{
    f32 point[3];
    f32 y;
    u16 selector;
    f32 cos_high;
    f32 sin_high;
    f32 vx;
    f32 vz;
    f32 len;
    void *anim;
    f32 cosine_high_angle;
    f32 sine_high_angle;
    f32 sine_heading;
    f32 cosine_heading;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        anim = (void *)zoid->anim_data;
        if (anim != 0) {
            cosine_high_angle = zoid->high_angle;
            cos_high = cosf(cosine_high_angle);
            sine_high_angle = zoid->high_angle;
            sin_high = sinf(sine_high_angle);
            sine_heading = zoid->heading;
            vx = zoid->field_1C90[1] * sinf(sine_heading);
            cosine_heading = zoid->heading;
            vz = zoid->field_1C90[1] * cosf(cosine_heading);
            len = sLenXZ(vx, vz);
            point[0] = zoid->position[0] + vx * cos_high;
            point[1] = zoid->position[1];
            point[2] = zoid->position[2] + vz * cos_high;
            y = zdColPosY(point, &selector);
            zoid->ground_polygon = selector;
            if (selector == 0xffff) {
                getWarn(zoid->position, point);
                zoid->heading += ZoidCalcAngle(zoid, (Vec3 *)point);
            } else {
                zoid->position[0] += vx * cos_high;
                zoid->position[2] += vz * cos_high;
                zoid->position[1] -= len * sin_high;
                ZoidSisei(zoid);
            }
        }
    }
}
