#include "zoid3.h"
#include "ground_collision.h"

extern GroundMask GXColorZoid;
extern f32 sinf(f32);
extern f32 cosf(f32);
extern f32 atan2f(f32 y, f32 x);
extern f32 zdColPosY(f32 *point, u16 *polygon);
extern s32 zdClimb(ZoidState *zoid, Vec3 *point);

static inline f32 wsinf(f32 x)
{
    return sinf(x);
}

static inline f32 wcosf(f32 x)
{
    return cosf(x);
}

static inline f32 watan2f(f32 y, f32 x)
{
    return atan2f(y, x);
}

void zdStop1Susumu(ZoidState *zoid)
{
    u8 *info;
    u8 flags;
    s32 i;
    s32 blocked;
    f32 c[3];
    f32 n[3];
    f32 d[3];
    f32 a[3];
    f32 b[3];
    u16 sel;
    void *anim;
    GroundMask mask;
    f32 angle;
    f32 dy;

    info = (u8 *)zoid->slider_info;
    anim = zoid->anim_data;
    if (info != 0) {
        flags = info[0x712];
        for (i = 0; i < 3; i++) {
            c[i] = zoid->position[i];
            a[i] = zoid->position[i];
            b[i] = zoid->position[i];
        }
        a[1] = zoid->field_1A7C->matrix[1][3];
        b[1] = zoid->field_1A7C->matrix[1][3];
        d[0] = zoid->field_1D60 * wsinf(zoid->field_1D5C);
        d[1] = 0.0f;
        d[2] = zoid->field_1D60 * wcosf(zoid->field_1D5C);
        c[1] = zdColPosY(c, 0);
        n[0] = zoid->field_1D60 * wsinf(zoid->field_1D5C) + c[0];
        n[1] = c[1];
        n[2] = zoid->field_1D60 * wcosf(zoid->field_1D5C) + c[2];
        n[1] = zdColPosY(n, &sel);
        if (sel == 0xFFFF) {
            zoid->field_1D60 = 0.0f;
            zoid->field_1C90[2] = 0.0f;
            zoid->field_1C90[0] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
            return;
        }
        if (zdClimb(zoid, (Vec3 *)n) != 0) {
            zoid->field_1D60 = 0.0f;
            zoid->field_1C90[2] = 0.0f;
            zoid->field_1C90[0] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
            return;
        }
        for (i = 0; i < 3; i++) {
            a[i] -= d[i];
            b[i] += 5.0f * d[i];
        }
        blocked = 0;
        if (zoid->grounded != 0) {
            if ((flags & 1) != 0 && *(u16 *)(zoid->head_coobj + 0x28) != 0xFFFF) {
                blocked = 1;
            }
            if ((flags & 2) != 0 && *(u16 *)(zoid->neck_coobj + 0x28) != 0xFFFF) {
                blocked = 1;
            }
            if ((flags & 4) != 0 && *(u16 *)(zoid->bust_coobj + 0x28) != 0xFFFF) {
                blocked = 1;
            }
            if ((flags & 8) != 0 && *(u16 *)(zoid->bust_coobj + 0x28) != 0xFFFF) {
                blocked = 1;
            }
        }
        if (blocked != 0) {
            zoid->field_1D60 = 0.0f;
            zoid->field_1C90[2] = 0.0f;
            zoid->field_1C90[0] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
            return;
        }
        mask = GXColorZoid;
        if (10000.0f != sColPt((Vec3 *)a, (Vec3 *)b, &mask)) {
            zoid->field_1D60 = 0.0f;
            zoid->field_1C90[2] = 0.0f;
            zoid->field_1C90[0] = 0.0f;
            zoid->field_1C90[1] = 0.0f;
            return;
        }
        if (0.0f != zoid->field_1D60) {
            dy = n[1] - c[1];
            angle = watan2f(dy, zoid->field_1D60);
            if (dy > 0.0f) {
                zoid->field_1D60 = zoid->field_1D60 * wcosf(angle);
                if (zoid->field_1D60 < 0.0f) {
                    zoid->field_1D60 = 0.0f;
                }
                n[0] = zoid->field_1D60 * wsinf(zoid->field_1D5C) + c[0];
                n[1] = c[1];
                n[2] = zoid->field_1D60 * wcosf(zoid->field_1D5C) + c[2];
                n[1] = zdColPosY(n, &sel);
            }
            if (dy < 0.0f && dy < -0.55) {
                zoid->position[0] = n[0];
                zoid->position[2] = n[2];
                zoid->action = 2;
                zoid->jump_phase = 0x20;
                return;
            }
        }
        for (i = 0; i < 3; i++) {
            zoid->position[i] = n[i];
        }
    }
}
