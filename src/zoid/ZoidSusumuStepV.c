#include "zoid3.h"
#include "ground_collision.h"

extern GroundMask GXColorZoid;
extern void ZoidSisei(ZoidState *zoid);
extern f32 sLenPoint3dR(f32 *point);
extern f32 zdColPosY(f32 *point, u16 *selector);

void ZoidSusumuStepV(ZoidState *zoid)
{
    f32 length;
    f32 reach;
    s32 i;
    f32 y;
    u16 selector;
    void *anim;
    f32 step[3];
    f32 start[3];
    f32 end[3];
    GroundMask mask;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        anim = zoid->anim_data;
        ZoidSisei(zoid);
        length = sLenPoint3dR(zoid->launch_velocity);
        if (length > 1.8) {
            for (i = 0; i < 3; i++) {
                step[i] = 1.8 * zoid->launch_velocity[i] / length;
            }
        } else {
            for (i = 0; i < 3; i++) {
                step[i] = zoid->launch_velocity[i];
            }
        }
        for (i = 0; i < 3; i++) {
            start[i] = zoid->position[i] + 3.0f * step[i];
            end[i] = zoid->position[i] - 2.0f * step[i];
        }
        start[1] = zoid->field_1A7C->matrix[1][3];
        end[1] = zoid->field_1A7C->matrix[1][3];
        reach = sLenPoint3dR(start);
        if (0.0f == reach) {
            return;
        }
        mask = GXColorZoid;
        reach = sColPt((Vec3 *)end, (Vec3 *)start, &mask);
        if (10000.0f != reach) {
            for (i = 0; i < 3; i++) {
                if (i != 1) {
                    step[i] = 0.0f;
                    zoid->launch_velocity[i] = 0.0f;
                }
            }
        }
        for (i = 0; i < 3; i++) {
            zoid->position[i] += step[i];
        }
        zoid->launch_velocity[1] -= 0.04;
        length = sLenPoint3dR(zoid->launch_velocity);
        if (length > 1.8) {
            for (i = 0; i < 3; i++) {
                zoid->launch_velocity[i] = 1.8 * zoid->launch_velocity[i] / length;
            }
        }
        y = zdColPosY(zoid->position, &selector);
        zoid->ground_polygon = selector;
        if (selector == 0xFFFF) {
            zoid->launch_velocity[0] = 0.5 * (zoid->field_1C24[0] - zoid->position[0]);
            zoid->launch_velocity[2] = 0.5 * (zoid->field_1C24[2] - zoid->position[2]);
            zoid->position[0] = zoid->previous_position[0];
            zoid->position[2] = zoid->previous_position[2];
        }
    }
}
