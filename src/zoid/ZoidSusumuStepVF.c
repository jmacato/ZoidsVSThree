#include "zoid3.h"
#include "ground_collision.h"

extern GroundMask GXColorZoid;
extern void ZoidSisei(ZoidState *zoid);
extern f32 sLenPoint3dR(Vec3 *point);
extern f32 zdColPosY(f32 *point, u16 *polygon);
extern void zdLimitHigh(ZoidState *zoid);
extern void getWarn(f32 *position, f32 *out);
extern f32 ZoidCalcAngle(ZoidState *zoid, f32 *point);

void ZoidSusumuStepVF(ZoidState *zoid, s32 flag)
{
    u16 sel;
    void *anim;
    f32 p[3];
    f32 q[3];
    f32 w[3];
    f32 z[3];
    f32 t[3];
    GroundMask mask;
    f32 length;
    f32 step = 1.0f;
    f32 y;
    s32 i;

    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        anim = zoid->anim_data;
        ZoidSisei(zoid);
        if (flag != 0) {
            step = 0.5f;
        }
        zoid->launch_velocity[1] = 0.0f;
        zoid->step_launch_y = 0.0f;
        for (i = 0; i < 3; i++) {
            t[i] = zoid->launch_velocity[i] + (&zoid->step_launch_x)[i] * step;
            p[i] = zoid->position[i] + t[i];
            q[i] = zoid->position[i];
        }
        q[1] = zoid->field_1A7C->matrix[1][3];
        length = sLenPoint3dR((Vec3 *)t);
        if (0.0f == length) {
            return;
        }
        for (i = 0; i < 3; i++) {
            w[i] = q[i] + (*(HSD_JObj **)zoid->body_coobj)->scale.x * (t[i] / length) / 2.0f;
            z[i] = q[i] - (*(HSD_JObj **)zoid->body_coobj)->scale.x * (t[i] / length) / 4.0f;
        }
        mask = GXColorZoid;
        y = sColPt((Vec3 *)z, (Vec3 *)w, &mask);
        if (zoid->field_1EAC & 1) {
            y = 0.0f;
        }
        if (y < 0.5) {
            (&zoid->step_launch_x)[i] = 0.0f;
            zoid->launch_velocity[i] = 0.0f;
        }
        if (10000.0f != y) {
            for (i = 0; i < 3; i++) {
                (&zoid->step_launch_x)[i] *= 0.5;
                zoid->launch_velocity[i] *= 0.99;
                t[i] = (&zoid->step_launch_x)[i] * step + zoid->launch_velocity[i];
                p[i] = zoid->position[i] + t[i];
            }
        }
        for (i = 0; i < 3; i++) {
            zoid->position[i] = p[i];
        }
        zdLimitHigh(zoid);
        y = zdColPosY(p, &sel);
        if (sel == 0xFFFF) {
            for (i = 0; i < 3; i++) {
                zoid->position[i] = zoid->previous_position[i];
                zoid->launch_velocity[i] = 0.0f;
                (&zoid->step_launch_x)[i] = 0.0f;
            }
            zdLimitHigh(zoid);
            getWarn(zoid->position, p);
            zoid->heading += ZoidCalcAngle(zoid, p);
        }
        length = y - zoid->position[1];
        if (length > 0.0f) {
            zoid->height_offset_speed = 0.0f;
            zoid->height_offset -= length;
            zoid->position[1] += length;
        }
        zoid->ground_polygon = sel;
    }
}
