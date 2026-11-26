#include "zoid3.h"
#include "ground_collision.h"
#pragma readonly_strings on

extern GroundMask GXColorZoid;
extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);
extern void dummyFunc(const char *);
extern void sLinear1D(f32 *value, f32 target, f32 step);
extern void antiV3(ZoidState *zoid);
extern void angLimit(f32 *angle);
extern f32 sColPtN(Vec3 *start, Vec3 *end, GroundMask *mask, u16 *selector);
extern f32 sColPt(Vec3 *start, Vec3 *end, GroundMask *mask);
extern s32 chkSusumu(void *joint, f32 *point);
extern void ZoidSisei(ZoidState *zoid);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void getWarn(f32 *position, f32 *point);
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);
extern f32 zdGetBasePoly(ZoidState *zoid, f32 *point);

static inline f32 wsinf(f32 x)
{
    return sinf(x);
}

static inline f32 wcosf(f32 x)
{
    return cosf(x);
}

#define DEG(x) (2.0 * (3.1415926 * (x)) / 360.0)

static inline f32 fabsf(f32 x)
{
    *(u32 *)&x &= 0x7FFFFFFF;
    return x;
}

void ZoidWalkSusumu3(ZoidState *zoid)
{
    f32 next[3];
    f32 cur[3];
    f32 far1[3];
    f32 far2[3];
    f32 start[3];
    f32 step[3];
    u16 selector2;
    u16 selector;
    f32 diff;
    f32 point[3];
    GroundMask mask1;
    GroundMask mask2;
    u8 *control;
    f32 target;
    f32 ry;
    f32 dir;
    f32 limit;
    f32 angle;
    f32 dx;
    f32 gap;
    f32 dz;
    f32 delta;
    f32 ground_y;
    GroundPolygon *poly;
    Vec3 *normal;
    s32 hit;
    s32 blocked;
    s32 anim;
    s32 i;

    dummyFunc("WkSu3>");
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        control = (u8 *)zoid->anim_data;
        target = zoid->steer;
        ry = zoid->f_base_ry;
        if (ry < target) {
            dir = 0.17453292f;
        }
        if (ry > target) {
            dir = -0.17453292f;
        }
        {
            f32 turn_step = 0.0052359877f;
            sLinear1D(&zoid->f_base_ry_speed, dir, turn_step);
        }
        ry += zoid->f_base_ry_speed;
        if (dir > 0.0f && ry > target) {
            ry = target;
        }
        if (dir < 0.0f && ry < target) {
            ry = target;
        }
        if (ry > DEG((f32) * (s32 *)(control + 0xC8))) {
            ry = DEG((f32) * (s32 *)(control + 0xC8));
        }
        if (ry < DEG((f32) - *(s32 *)(control + 0xC8))) {
            ry = DEG((f32) - *(s32 *)(control + 0xC8));
        }
        if (zoid->f_base_joint != 0) {
            zoid->f_base_ry = ry;
        }
        if (zoid->f_base_ry == zoid->steer) {
            zoid->f_base_ry_speed = 0.0f;
        }
        if (zoid->field_1ACC != 0) {
            angle = zoid->senter_roll;
            if (zoid->current_animation == 5 || zoid->current_animation == 4) {
                limit = zoid->steer;
            } else {
                limit = 0.0f;
            }
            if (limit < DEG((f32) - *(s32 *)(control + 0x98))) {
                limit = DEG((f32) - *(s32 *)(control + 0x98));
            }
            if (limit > DEG((f32) * (s32 *)(control + 0x98))) {
                limit = DEG((f32) * (s32 *)(control + 0x98));
            }
            dir = 0.0f;
            if (angle < limit) {
                dir = 0.17453292f;
            }
            if (angle > limit) {
                dir = -0.17453292f;
            }
            sLinear1D(&zoid->senter_roll_speed, dir, 0.00087266463f);
            angle += zoid->senter_roll_speed;
            if (dir > 0.0f && angle > limit) {
                angle = limit;
            }
            if (dir < 0.0f && angle < limit) {
                angle = limit;
            }
            if (angle < DEG((f32) - *(s32 *)(control + 0x98))) {
                angle = DEG((f32) - *(s32 *)(control + 0x98));
            }
            if (angle > DEG((f32) * (s32 *)(control + 0x98))) {
                angle = DEG((f32) * (s32 *)(control + 0x98));
            }
            if (angle == limit) {
                zoid->senter_roll_speed = 0.0f;
            }
            zoid->senter_roll = angle;
        }
        antiV3(zoid);
        for (i = 0; i < 3; i++) {
            cur[i] = zoid->position[i];
            start[i] = zoid->position[i];
            far1[i] = zoid->position[i];
            far2[i] = zoid->position[i];
        }
        start[1] = zoid->field_1A7C->matrix[1][3];
        far1[1] = zoid->field_1A7C->matrix[1][3];
        far2[1] = zoid->field_1A7C->matrix[1][3];
        step[0] = zoid->field_1C90[2] * wsinf(zoid->heading) * wcosf(zoid->high_angle);
        step[1] = zoid->field_1C90[2] * wsinf(-zoid->high_angle);
        step[2] = zoid->field_1C90[2] * wcosf(zoid->heading) * wcosf(zoid->high_angle);
        for (i = 0; i < 3; i++) {
            start[i] -= 2.0f * step[i];
            far1[i] += 10.0f * step[i];
            far2[i] += 20.0f * step[i];
        }
        mask1 = GXColorZoid;
        blocked = 0;
        if (10000.0f != sColPtN((Vec3 *)start, (Vec3 *)far2, &mask1, &selector)) {
            normal = 0;
            if (selector != GROUND_POLYGON_NONE) {
                poly = &grdcPolygon[selector];
                if (poly->normal_index != GROUND_POLYGON_NONE) {
                    normal = &grdcNormal[poly->normal_index];
                }
            }
            blocked = 1;
            if (normal != 0) {
                if (normal->y < 0.0f) {
                    blocked = 2;
                }
                if (start[1] < far2[1]) {
                    if (fabsf(normal->y) > 0.7) {
                        blocked = 2;
                    }
                }
            }
        }
        mask2 = GXColorZoid;
        hit = 0;
        if (10000.0f != sColPt((Vec3 *)start, (Vec3 *)far1, &mask2)) {
            hit = 1;
        }
        if (zoid->field_1C90[2] > 0.0f) {
            if (hit == 0 && *(s32 *)(control + 0) != 0) {
                hit = chkSusumu(*(void **)zoid->head_coobj, step);
            }
            if (hit == 0 && *(s32 *)(control + 4) != 0) {
                hit = chkSusumu(*(void **)zoid->neck_coobj, step);
            }
        }
        if (hit != 0) {
            zoid->field_1CB8 = 15;
            zoid->field_1CBC = zoid->heading;
            angLimit(&zoid->field_1CBC);
            zoid->field_1C90[0] = 0.0f;
            zoid->field_1C90[2] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
        }
        if (zoid->field_1CB8 != 0) {
            diff = zoid->heading;
            diff = diff - zoid->field_1CBC;
            angLimit(&diff);
            diff = fabsf(diff);
            if (diff < DEG(10)) {
                zoid->field_1C90[0] = 0.0f;
                zoid->field_1C90[2] = 0.0f;
                zoid->field_1C90[1] = 0.0f;
            }
        }
        ZoidSisei(zoid);
        for (i = 0; i < 3; i++) {
            cur[i] = zoid->position[i];
        }
        next[0] = zoid->field_1C90[2] * wsinf(zoid->heading) * wcosf(zoid->high_angle) + cur[0];
        next[1] = zoid->field_1C90[2] * wsinf(-zoid->high_angle) + cur[1];
        next[2] = zoid->field_1C90[2] * wcosf(zoid->heading) * wcosf(zoid->high_angle) + cur[2];
        ground_y = zdColPosY(next, &selector2);
        if (selector2 == GROUND_POLYGON_NONE) {
            for (i = 0; i < 3; i++) {
                zoid->position[i] = zoid->previous_position[i];
                cur[i] = zoid->position[i];
                point[i] = zoid->position[i];
            }
            getWarn(zoid->position, point);
            zoid->heading += ZoidCalcAngle(zoid, (Vec3 *)point);
            return;
        }
        if (ground_y >= zoid->field_1AA8 && ground_y > next[1]) {
            ground_y = next[1];
        }
        if (next[1] < ground_y && blocked == 0) {
            blocked = 1;
        }
        if (blocked & 1) {
            if (zoid->high_angle > -DEG(60)) {
                sLinear1D(&zoid->high_angle, -DEG(60), DEG(5));
            }
        }
        if (blocked & 2) {
            if (zoid->high_angle < DEG(60)) {
                sLinear1D(&zoid->high_angle, DEG(60), DEG(10));
            }
        }
        dx = next[0] - zoid->position[0];
        ground_y = next[1] - zoid->position[1];
        dz = next[2] - zoid->position[2];
        target = dx * dx + ground_y * ground_y + dz * dz;
        delta = zoid->field_1C90[1] * zoid->field_1C90[1];
        gap = delta - target;
        if (zoid->field_1C90[1] >= 0.0f && zoid->field_1C90[2] >= 0.0f) {
            if (gap > 0.0f) {
                zoid->field_1C90[2] += 0.05;
                if (zoid->field_1C90[2] > zoid->field_1C90[1]) {
                    zoid->field_1C90[2] = zoid->field_1C90[1];
                }
            }
            if (gap < 0.0f) {
                zoid->field_1C90[2] -= 0.05;
                if (zoid->field_1C90[2] < 0.0f) {
                    zoid->field_1C90[2] = 0.0f;
                }
                if (zoid->field_1C90[2] < zoid->field_1C90[1]) {
                    zoid->field_1C90[2] = zoid->field_1C90[1];
                }
            }
        } else if (zoid->field_1C90[1] >= 0.0f && zoid->field_1C90[2] < 0.0f) {
            zoid->field_1C90[2] += 0.05;
        } else if (zoid->field_1C90[1] < 0.0f && zoid->field_1C90[2] >= 0.0f) {
            zoid->field_1C90[2] -= 0.05;
        } else if (zoid->field_1C90[1] < 0.0f && zoid->field_1C90[2] < 0.0f) {
            if (gap > 0.0f) {
                zoid->field_1C90[2] -= 0.05;
                if (zoid->field_1C90[2] < zoid->field_1C90[1]) {
                    zoid->field_1C90[2] = zoid->field_1C90[1];
                }
            }
            if (gap < 0.0f) {
                zoid->field_1C90[2] += 0.05;
                if (zoid->field_1C90[2] > 0.0f) {
                    zoid->field_1C90[2] = 0.0f;
                }
                if (zoid->field_1C90[2] > zoid->field_1C90[1]) {
                    zoid->field_1C90[2] = zoid->field_1C90[1];
                }
            }
        }
        anim = zoid->current_animation;
        if (anim == 2 || anim == 1) {
            (void)0;
        }
        zoid->position[0] += dx;
        zoid->position[1] += ground_y;
        zoid->position[2] += dz;
        zoid->ground_height = zdGetBasePoly(zoid, next);
    }
}
