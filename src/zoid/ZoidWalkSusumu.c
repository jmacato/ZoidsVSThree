#include "zoid3.h"
#include "ground_collision.h"
#pragma readonly_strings on

extern GroundMask GXColorZoid;
extern f32 sinf(f32 angle);
extern f32 cosf(f32 angle);
extern void dummyFunc(const char *);
extern void sLinear1D(f32 *value, f32 target, f32 step);
extern void angLimit(f32 *angle);
extern f32 sColPt(Vec3 *start, Vec3 *end, GroundMask *mask);
extern s32 chkSusumu(void *joint, f32 *point);
extern void ZoidSisei(ZoidState *zoid);
extern f32 zdColPosY(f32 *point, u16 *selector);
extern void getWarn(f32 *position, f32 *point);
extern f32 ZoidCalcAngle(ZoidState *zoid, Vec3 *point);
extern s32 zdClimb(ZoidState *zoid, Vec3 *point);
extern void ftSlide(ZoidState *zoid);

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

void ZoidWalkSusumu(ZoidState *zoid)
{
    f32 next[3];
    f32 cur[3];
    f32 far1[3];
    f32 start[3];
    f32 step[3];
    u16 selector;
    u16 selector2;
    f32 angle;
    f32 prev;
    f32 diff;
    f32 point[3];
    GroundMask mask;
    u8 *control;
    f32 target;
    f32 speed;
    f32 dy;
    f32 limit;
    f32 gap;
    f32 move;
    f32 dx;
    f32 dz;
    f32 roll;
    f32 delta;
    s32 hit;
    s32 anim;
    s32 i;

    dummyFunc("WkSu>");
    if (zoid != (void *)0 && zoid->joint != (void *)0) {
        control = (u8 *)zoid->anim_data;
        target = zoid->steer;
        if (zoid->f_base_joint != 0) {
            if (fabsf(zoid->f_base_ry - target) < DEG(5)) {
                zoid->f_base_ry = target;
            }
            if (zoid->f_base_ry < target) {
                zoid->f_base_ry += DEG(3);
                if (zoid->f_base_ry > target) {
                    zoid->f_base_ry = target;
                }
            }
            if (zoid->f_base_ry > target) {
                zoid->f_base_ry -= DEG(3);
                if (zoid->f_base_ry < target) {
                    zoid->f_base_ry = target;
                }
            }
            if (zoid->f_base_ry > DEG((f32) * (s32 *)(control + 0xC8))) {
                zoid->f_base_ry = DEG((f32) * (s32 *)(control + 0xC8));
            }
            if (zoid->f_base_ry < -DEG((f32) * (s32 *)(control + 0xC8))) {
                zoid->f_base_ry = DEG((f32) - *(s32 *)(control + 0xC8));
            }
        }
        dummyFunc("Su2.");
        if (zoid->field_1ACC != 0) {
            angle = zoid->senter_roll;
            prev = angle;
            if (zoid->current_animation == 5 || zoid->current_animation == 4) {
                limit = zoid->steer * zoid->field_1C90[2] * 10.0f;
            } else {
                limit = 0.0f;
            }
            if (limit < DEG((f32) - *(s32 *)(control + 0x98))) {
                limit = DEG((f32) - *(s32 *)(control + 0x98));
            }
            if (limit > DEG((f32) * (s32 *)(control + 0x98))) {
                limit = DEG((f32) * (s32 *)(control + 0x98));
            }
            sLinear1D(&angle, limit, 0.017453292f);
            zoid->senter_roll = angle;
        }
        ZoidSisei(zoid);
        dummyFunc("Su3.");
        if (zoid->b_base_joint != 0) {
            speed = zoid->field_1C90[2];
            roll = zoid->ground_rz + zoid->senter_roll;
            if (speed > 1.0f) {
                speed = 1.0f;
            }
            if (speed < 0.1) {
                speed = 0.0f;
            }
            roll *= speed;
            zoid->field_1CE8 = roll;
            speed = fabsf(roll) - DEG(45);
            if (speed > 0.0f) {
                zoid->slide_speed = roll > 0.0f ? speed : -speed;
            } else {
                zoid->slide_speed = 0.0f;
            }
        }
        if (zoid->field_1CF8 != 0) {
            zoid->field_1CF8--;
            zoid->field_1C90[0] *= 0.9;
            zoid->field_1C90[2] *= 0.9;
            zoid->field_1C90[1] *= 0.9;
        }
        dummyFunc("Su4.");
        for (i = 0; i < 3; i++) {
            cur[i] = zoid->position[i];
            start[i] = zoid->position[i];
            far1[i] = zoid->position[i];
        }
        start[1] = zoid->field_1A7C->matrix[1][3];
        far1[1] = zoid->field_1A7C->matrix[1][3];
        step[0] = zoid->field_1C90[2] * wsinf(zoid->heading);
        step[1] = 0.0f;
        step[2] = zoid->field_1C90[2] * wcosf(zoid->heading);
        for (i = 0; i < 3; i++) {
            start[i] -= 2.0f * step[i];
            far1[i] += 10.0f * step[i];
        }
        if (zoid->field_1C90[2] >= 0.0f) {
            far1[1] += fabsf(15.0f * zoid->field_1C90[2]);
        } else {
            far1[1] += fabsf(10.0f * zoid->field_1C90[2]);
        }
        dummyFunc("Su4c.");
        hit = 0;
        if (0.0f != zoid->field_1C90[2]) {
            mask = GXColorZoid;
            if (10000.0f != sColPt((Vec3 *)start, (Vec3 *)far1, &mask)) {
                hit = 1;
            }
        }
        dummyFunc("Su4d.");
        if (zoid->field_1C90[2] < 0.0f && *(u16 *)(zoid->hip_coobj + 0x28) != 0xFFFF) {
            hit = 1;
        }
        dummyFunc("Su4e.");
        if (zoid->field_1C90[2] > 0.0f && hit == 0 && *(s32 *)(control + 4) != 0) {
            hit = chkSusumu(*(void **)zoid->neck_coobj, step);
        }
        dummyFunc("Su5.");
        if (hit != 0) {
            zoid->field_1CB8 = 30;
            zoid->field_1CBC = zoid->heading;
            if (zoid->field_1C90[2] < 0.0f) {
                zoid->field_1CBC += 3.1415926;
            }
            angLimit(&zoid->field_1CBC);
            zoid->field_1C90[0] = 0.0f;
            zoid->field_1C90[2] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
        }
        if (zoid->field_1CB8 != 0) {
            diff = zoid->heading;
            if (zoid->field_1C90[2] < 0.0f) {
                diff += 3.1415926;
            }
            diff = diff - zoid->field_1CBC;
            angLimit(&diff);
            diff = fabsf(diff);
        }
        dummyFunc("Su6.");
        cur[1] = zdColPosY(cur, 0);
        next[0] = zoid->field_1C90[2] * wsinf(zoid->heading) + cur[0];
        next[1] = cur[1];
        next[2] = zoid->field_1C90[2] * wcosf(zoid->heading) + cur[2];
        next[1] = zdColPosY(next, &selector2);
        if (selector2 == GROUND_POLYGON_NONE) {
            for (i = 0; i < 3; i++) {
                zoid->position[i] = zoid->previous_position[i];
            }
            getWarn(zoid->position, point);
            zoid->heading += ZoidCalcAngle(zoid, (Vec3 *)point);
            return;
        }
        dummyFunc("Su7.");
        if (zdClimb(zoid, (Vec3 *)next) != 0) {
            zoid->field_1C90[2] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
            zoid->field_1C90[0] = 0.0f;
            if (zoid->ground_normal != 0) {
                zoid->position[0] += 0.02 * zoid->ground_normal->x;
                zoid->position[2] += 0.02 * zoid->ground_normal->z;
                return;
            }
            for (i = 0; i < 3; i++) {
                zoid->position[i] = zoid->previous_position[i];
            }
            return;
        }
        dummyFunc("Su8.");
        dx = next[0] - zoid->position[0];
        dy = next[1] - zoid->ground_height;
        (void)(-dy);
        speed = zoid->field_1C90[1] * dy;
        dz = next[2] - zoid->position[2];
        target = dx * dx + dy * dy + dz * dz;
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
        dummyFunc("Su9.");
        anim = zoid->current_animation;
        move = zoid->field_1C90[2];
        if (anim == 2 || anim == 1) {
            move = 0.0f;
        }
        dx = move * wsinf(zoid->heading);
        dz = move * wcosf(zoid->heading);
        dy = -move * wsinf(zoid->ground_rx);
        if (dy >= 0.0f) {
            dy = 0.0f;
        }
        zoid->position[0] += dx;
        zoid->position[1] += dy;
        zoid->position[2] += dz;
        ftSlide(zoid);
    }
}
