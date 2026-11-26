#include "zoid3.h"

extern void ZoidSisei(ZoidState *zoid);
extern f32 sLenPoint3dR(Vec3 *point);
extern f32 zdColPosY(Vec3 *point, u16 *selector);
extern void zdGetDeadPoly(ZoidState *zoid, Vec3 *point);

void ZoidSusumuV(ZoidState *zoid)
{
    s32 i;
    f32 length;
    f32 ground_y;
    f32 depth;
    u16 selector;
    ZoidControlData *control;
    f32 scaled[3];
    u16 saved_selector;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        control = (ZoidControlData *)zoid->anim_data;
        ZoidSisei(zoid);
        length = sLenPoint3dR((Vec3 *)zoid->launch_velocity);
        if (length > 2.8) {
            for (i = 0; i < 3; i++) {
                scaled[i] = 2.8 * zoid->launch_velocity[i] / length;
            }
        } else {
            for (i = 0; i < 3; i++) {
                scaled[i] = zoid->launch_velocity[i];
            }
        }
        for (i = 0; i < 3; i++) {
            zoid->position[i] += scaled[i];
        }
        zoid->launch_velocity[1] -= 0.04;
        length = sLenPoint3dR((Vec3 *)zoid->launch_velocity);
        if (length > 2.8) {
            for (i = 0; i < 3; i++) {
                zoid->launch_velocity[i] = 2.8 * zoid->launch_velocity[i] / length;
            }
        }
        zdGetDeadPoly(zoid, (Vec3 *)zoid->position);
        ground_y = zdColPosY((Vec3 *)zoid->position, &selector);
        if (selector == 0xffff) {
            for (i = 0; i < 3; i++) {
                zoid->position[i] = zoid->previous_position[i];
                if (i != 1) {
                    zoid->launch_velocity[i] = -zoid->launch_velocity[i];
                }
            }
        }
        saved_selector = selector;
        if (ground_y > zoid->field_1AA8 && zoid->field_0170 != 0) {
            ground_y = zoid->position[1];
            zoid->field_1EB8 = selector;
            selector = 0xffff;
        }
        depth = ground_y - zoid->position[1];
        if (depth > 0.0f) {
            zoid->height_offset_speed = 0.0f;
            zoid->height_offset -= depth;
            zoid->position[1] += depth;
        }
        zoid->ground_polygon = selector;
        zoid->field_1EB8 = saved_selector;
    }
}
